<Type> -> <INTEGER>
<VarDecl> -> <IDENTIFIER
<IdentifierList> -> <VarDecl>
<VarDecl> -> <IDENTIFIER
<IdentifierList> -> <IdentifierList> <CM> <VarDecl>
<VarDecl> -> <IDENTIFIER
<IdentifierList> -> <IdentifierList> <CM> <VarDecl>
<VarDecl> -> <IDENTIFIER
<IdentifierList> -> <IdentifierList> <CM> <VarDecl>
<VarDecl> -> <IDENTIFIER
<IdentifierList> -> <IdentifierList> <CM> <VarDecl>
<VarDecl> -> <IDENTIFIER
<IdentifierList> -> <IdentifierList> <CM> <VarDecl>
<DeclList> -> <Type> <IdentifierList> <SC>
<Type> -> <INTEGER>
<FunctionDecl> ->  <Type> <IDENTIFIER> <LP> <RP> <LBR>
<ProcedureHead> -> <FunctionDecl>
<StringConstant> -> <STRING>
"i = "
<IOStatement> -> <WRITE> <LP> <StringConstant> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <Statement>
i
<Variable> -> <IDENTIFIER>
<IOStatement> -> <READ> <LP> <Variable> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
<StringConstant> -> <STRING>
"j = "
<IOStatement> -> <WRITE> <LP> <StringConstant> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
j
<Variable> -> <IDENTIFIER>
<IOStatement> -> <READ> <LP> <Variable> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
<StringConstant> -> <STRING>
"k = "
<IOStatement> -> <WRITE> <LP> <StringConstant> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
k
<Variable> -> <IDENTIFIER>
<IOStatement> -> <READ> <LP> <Variable> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
<StringConstant> -> <STRING>
"l = "
<IOStatement> -> <WRITE> <LP> <StringConstant> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
l
<Variable> -> <IDENTIFIER>
<IOStatement> -> <READ> <LP> <Variable> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
<StringConstant> -> <STRING>
"m = "
<IOStatement> -> <WRITE> <LP> <StringConstant> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
m
<Variable> -> <IDENTIFIER>
<IOStatement> -> <READ> <LP> <Variable> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
n
<Variable> -> <IDENTIFIER>
k
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
j
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
l
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<AddExpr> -> <AddExpr>4 <PLUS> <MulExpr>2 
<SimpleExpr> -> <SimpleExpr> <LT> <AddExpr> 
<Expr> -> <SimpleExpr>
i
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
k
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<SimpleExpr> -> <SimpleExpr> <NE> <AddExpr> 
<Expr> -> <SimpleExpr>
<Factor> -> <LP> <Expr> <RP>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
<Expr> -> <NOT> <SimpleExpr> 
<Factor> -> <LP> <Expr> <RP>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
<Expr> -> <Expr> <AND> <SimpleExpr> 
<Assignment> -> <Variable> <ASSIGN> <Expr> <SC>
<Statement> -> <Assignment>
<StatementList> -> <StatementList> <Statement>
n
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
<Expr> -> <SimpleExpr>
0
<IOStatement> -> <WRITE> <LP> <Expr> <RP> <SC>   0
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
i
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
l
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <MulExpr> <TIMES> <Factor> 
<SimpleExpr> -> <AddExpr>
j
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
k
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <MulExpr> <TIMES> <Factor> 
<SimpleExpr> -> <SimpleExpr> <GT> <AddExpr> 
<Expr> -> <SimpleExpr>
<Constant> -> <INTCON> 1
<Factor> -> <Constant>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
m
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<SimpleExpr> -> <SimpleExpr> <LE> <AddExpr> 
<Expr> -> <Expr> <OR> <SimpleExpr> 
1
<IOStatement> -> <WRITE> <LP> <Expr> <RP> <SC>   1
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
k
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
l
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <MulExpr> <TIMES> <Factor> 
<SimpleExpr> -> <AddExpr>
j
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
k
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<AddExpr> -> <AddExpr>4 <PLUS> <MulExpr>1 
l
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<AddExpr> -> <AddExpr>5 <PLUS> <MulExpr>2 
<SimpleExpr> -> <SimpleExpr> <GT> <AddExpr> 
<Expr> -> <SimpleExpr>
i
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
j
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<SimpleExpr> -> <SimpleExpr> <NE> <AddExpr> 
<Expr> -> <Expr> <AND> <SimpleExpr> 
l
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
n
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<SimpleExpr> -> <SimpleExpr> <GT> <AddExpr> 
<Expr> -> <Expr> <OR> <SimpleExpr> 
1
<IOStatement> -> <WRITE> <LP> <Expr> <RP> <SC>   1
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
l
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
j
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <MulExpr> <DIVIDE> <Factor> 
i
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<AddExpr> -> <AddExpr> <MINUS> <MulExpr> 
<SimpleExpr> -> <AddExpr>
m
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<SimpleExpr> -> <SimpleExpr> <GT> <AddExpr> 
<Expr> -> <SimpleExpr>
k
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
l
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
n
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <MulExpr> <TIMES> <Factor> 
<AddExpr> -> <AddExpr>1 <PLUS> <MulExpr>0 
<SimpleExpr> -> <AddExpr>
l
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
k
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
n
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <MulExpr> <TIMES> <Factor> 
<AddExpr> -> <AddExpr>2 <PLUS> <MulExpr>0 
<SimpleExpr> -> <SimpleExpr> <NE> <AddExpr> 
<Expr> -> <Expr> <AND> <SimpleExpr> 
0
<IOStatement> -> <WRITE> <LP> <Expr> <RP> <SC>   0
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
<ProcedureBody> -> <StatementList> <RBR>
<ProcedureDecl> -> <ProcedureHead> <ProcedureBody>
<Procedures> -> epsilon
<Procedures> -> <ProcedureDecl> <Procedures>
<Program> -> <DeclList> <Procedures>
