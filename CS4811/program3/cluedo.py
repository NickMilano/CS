import cnf

class Cluedo:
    suspects = ['sc', 'mu', 'wh', 'gr', 'pe', 'pl']
    weapons  = ['kn', 'cs', 're', 'ro', 'pi', 'wr']
    rooms    = ['ha', 'lo', 'di', 'ki', 'ba', 'co', 'bi', 'li', 'st']
    casefile = "cf"
    hands    = suspects + [casefile]
    cards    = suspects + weapons + rooms

    """
    Return ID for player/card pair from player/card indicies
    """
    @staticmethod
    def getIdentifierFromIndicies(hand, card):
        return hand * len(Cluedo.cards) + card + 1

    """
    Return ID for player/card pair from player/card names
    """
    @staticmethod
    def getIdentifierFromNames(hand, card):
        return Cluedo.getIdentifierFromIndicies(Cluedo.hands.index(hand), Cluedo.cards.index(card))


def deal(hand, cards):
    "Construct the CNF clauses for the given cards being in the specified hand"
    arr = []
    #Loop through all dealt cards, get the corresponding number and add it to array
    for c in cards:
        arr.append([Cluedo.getIdentifierFromNames(hand,c)])
    return arr

def axiom_card_exists():
    """
    Construct the CNF clauses which represents:
        'Each card is in at least one place'
    """
    ans = []
    arr = []
    #For every card
    for c in Cluedo.cards:
        if arr:
            ans.append(arr)
        arr = []
        #And for every hand
        for h in Cluedo.hands:
            #There is a number representing that card
            arr.append(Cluedo.getIdentifierFromNames(h,c))
    ans.append(arr)
    return ans

def axiom_card_unique():
    """
    Construct the CNF clauses which represents:
        'If a card is in one place, it can not be in another place'
    """
    ans = []
    arr = []
    #For every card
    for c in Cluedo.cards:
        if arr:
            #logic to make all the negated pairs
            temp = []
            for ind1 in range(len(arr)):
                for ind2 in range(ind1+1,len(arr)):
                        ans.append([- arr[ind1],- arr[ind2]])
        arr = []
        #And for every hand
        for h in Cluedo.hands:
            #There is a number representing that card
            arr.append(Cluedo.getIdentifierFromNames(h,c))
    #add the last section after breaking
    temp = []
    for ind1 in range(len(arr)):
        for ind2 in range(ind1+1,len(arr)):
            ans.append([- arr[ind1],- arr[ind2]])
    return ans

def axiom_casefile_exists():
    """
    Construct the CNF clauses which represents:
        'At least one card of each category is in the case file'
    """
    #suspects, weapons, rooms
    ans = []
    arr = []
    #For every card in suspects
    for c in Cluedo.suspects:
        #we add it
        arr.append(Cluedo.getIdentifierFromNames("cf",c))
    #add our clauses and reset array
    ans.append(arr)
    arr = []
    #repeat process for weapons and rooms
    for c in Cluedo.weapons:
        arr.append(Cluedo.getIdentifierFromNames("cf",c))
    ans.append(arr)
    arr = []
    for c in Cluedo.rooms:
        arr.append(Cluedo.getIdentifierFromNames("cf",c))
    ans.append(arr)
    return ans

def axiom_casefile_unique():
    """
    Construct the CNF clauses which represents:
        'No two cards in each category are in the case file'
    """
    ans = []
    #makes negated pairs for every pair from[0,n] for all lists
    for ind1 in range(len(Cluedo.suspects)):
        for ind2 in range(ind1+1,len(Cluedo.suspects)):
            ans.append([- Cluedo.getIdentifierFromNames("cf",Cluedo.suspects[ind1]),- Cluedo.getIdentifierFromNames("cf",Cluedo.suspects[ind2])])
        temp = []
    for ind1 in range(len(Cluedo.weapons)):
        for ind2 in range(ind1+1,len(Cluedo.weapons)):
            ans.append([- Cluedo.getIdentifierFromNames("cf",Cluedo.weapons[ind1]),- Cluedo.getIdentifierFromNames("cf",Cluedo.weapons[ind2])])
    temp = []
    for ind1 in range(len(Cluedo.rooms)):
        for ind2 in range(ind1+1,len(Cluedo.rooms)):
            ans.append([- Cluedo.getIdentifierFromNames("cf",Cluedo.rooms[ind1]),- Cluedo.getIdentifierFromNames("cf",Cluedo.rooms[ind2])])
    return ans

#helper function for finding all players that are between 2 players
def between(suggester, refuter):
    #takes the list of players and splices out all the ones not in between
    players = ['sc', 'mu', 'wh', 'gr', 'pe', 'pl']
    ind1 = players.index(suggester)+1
    ind2 = players.index(refuter)
    return players[ind1:ind2]

def suggest(suggester, card1, card2, card3, refuter, cardShown):
    "Construct the CNF clauses representing facts and/or clauses learned from a suggestion"
    #Order Scarlet, Mustard, White, Green, Peacock, Plum
    #Suggester = turn, card1 = a person, card 2 = a weapon, card 3 = room, refuter = person that has card1-3, cardShown = card or none
    players = ['sc', 'mu', 'wh', 'gr', 'pe', 'pl']
    cards = [card1, card2, card3]
    ans = []
    temp = []
    #Case 1 no refuter
    if refuter == None:
        #We can make assumptions about everyone except the suggester so remove them
        players.remove(suggester)
        #for the rest of the players they cannot have any of the suggested cards
        for p in players:
            for c in cards:
                ans.append([-Cluedo.getIdentifierFromNames(p, c)])
        return ans
    #Case 2 we cant see the card
    elif cardShown == None:
        #get any players that may have not been able to refute
        info = between(suggester, refuter)
        #for all those players they cannot have any of the 3 suggested cards
        for p in info:
            for c in cards:
                ans.append([-Cluedo.getIdentifierFromNames(p, c)])
        #But for the refuter they may have any 1 of the 3 cards
        for c in cards:
                temp.append(Cluedo.getIdentifierFromNames(refuter, c))
        ans.append(temp)
        return ans
    else:
        #we have all the parameters
        #check for potential players not able to refute
        info = between(suggester, refuter)
        #for all those players they cannot have any of the 3 suggested cards
        for p in info:
            for c in cards:
                ans.append([-Cluedo.getIdentifierFromNames(p, c)])
        #and for the card we see we know the refuter has that card
        ans.append([Cluedo.getIdentifierFromNames(refuter, cardShown)])
        return ans


def accuse(accuser, card1, card2, card3, correct):
    "Construct the CNF clauses representing facts and/or clauses learned from an accusation"
    #2 cases true or false
    cards = [card1, card2, card3]
    ans = []
    temp = []
    #If we are correct
    if correct == True:
        #All the cards are located in the casefile
        for c in cards:
            ans.append([Cluedo.getIdentifierFromNames("cf", c)])
        return ans
    else:
        #Otherwise out of all the accuser cards
        for c in cards:
            temp.append(Cluedo.getIdentifierFromNames(accuser, c))
        ans.append(temp)
        #Any number of them could be correct or incorrect but not all 3 were correct
        for c in cards:
            ans.append([- Cluedo.getIdentifierFromNames("cf", c)])
        return ans
