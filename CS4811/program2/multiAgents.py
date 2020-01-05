# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        #Finding closest food based on manhattanDistance
        foodList = newFood.asList()
        minDist = -1;
        for food in foodList:
            dist = util.manhattanDistance(newPos, food);
            if minDist >= dist or minDist == -1:
                minDist = dist

        #Finding distance to ghost as well as if we are next to a ghost
        distGhost = 1
        proxGhost = 0
        for ghost in successorGameState.getGhostPositions():
            dist = util.manhattanDistance(newPos, ghost)
            distGhost += dist
            if dist <= 1:
                proxGhost += 1

        #Scores returned are best when we are close to a food, far from a ghost, and not in the proximity of a ghost
        return successorGameState.getScore() + (1 / float(minDist)) - (1 / float(distGhost)) - proxGhost

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.

          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game

          gameState.isWin():
            Returns whether or not the game state is a winning state

          gameState.isLose():
            Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        def minimax(agent, depth, gameState):
            #Base case
            if gameState.isLose() or gameState.isWin() or depth == self.depth:
                return self.evaluationFunction(gameState)
            #If its pacmans turn we want to maximize result
            if agent == 0:
                return max(minimax(1, depth, gameState.generateSuccessor(agent, nextState)) for nextState in gameState.getLegalActions(agent))
            #Ghost turn we want to minimize result
            else:
                next = agent + 1
                if gameState.getNumAgents() == next:
                    next = 0
                if next == 0:
                    depth += 1
                return min(minimax(next, depth, gameState.generateSuccessor(agent, nextState)) for nextState in gameState.getLegalActions(agent))
        #base maximize
        maxAction = -1
        move = Directions.WEST
        for states in gameState.getLegalActions(0):
            util = minimax(1, 0, gameState.generateSuccessor(0, states))
            if util > maxAction or maxAction == -1:
                maxAction = util
                move = states
        return move

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        #maximizing function
        def maximize(agent, depth, gameState, a, b):
            #n starts as negative infinity and we want to find the max value for n
            n = float("-inf")
            for state in gameState.getLegalActions(agent):
                n = max(n, prune(1, depth, gameState.generateSuccessor(agent, state), a, b))
                if n > b:
                    return n
                a = max(a, n)
            return n

        #minimizing function
        def minimize(agent, depth, gameState, a, b):
            n = float("inf")
            next = agent + 1
            if gameState.getNumAgents() == next:
                next = 0
            if next == 0:
                depth +=1
            for state in gameState.getLegalActions(agent):
                n = min(n, prune(next, depth, gameState.generateSuccessor(agent, state), a, b))
                if n < a:
                    return n
                b = min(b, n)
            return n

        #pruning function
        def prune(agent, depth, gameState, a, b):
            if gameState.isLose() or gameState.isWin() or depth == self.depth:
                return self.evaluationFunction(gameState)
            if agent == 0:
                return maximize(agent, depth, gameState, a, b)
            else:
                return minimize(agent, depth, gameState, a, b)

        #base case pruning
        util = float("-inf")
        move = Directions.WEST
        a = float("-inf")
        b = float("inf")
        for state in gameState.getLegalActions(0):
            ghost = prune(1, 0, gameState.generateSuccessor(0, state), a, b)
            if ghost > util:
                util = ghost
                move = state
            if util > b:
                return util
            a = max(a, util)
        return move

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        "*** YOUR CODE HERE ***"
        util.raiseNotDefined()

def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction
