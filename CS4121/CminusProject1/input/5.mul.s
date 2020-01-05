<Type> -> <INTEGER>
<VarDecl> -> <IDENTIFIER
<IdentifierList> -> <VarDecl>
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
<Constant> -> <INTCON> 10
<Factor> -> <Constant>
<MulExpr> -> <Factor>
<Constant> -> <INTCON> 20
<Factor> -> <Constant>
<MulExpr> -> <MulExpr> <TIMES> <Factor> 
<SimpleExpr> -> <AddExpr>
<Expr> -> <SimpleExpr>
200
<IOStatement> -> <WRITE> <LP> <Expr> <RP> <SC>   200
<Statement> -> <IOStatement>
<StatementList> -> <Statement>
i
<Variable> -> <IDENTIFIER>
<Constant> -> <INTCON> 7
<Factor> -> <Constant>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
<Expr> -> <SimpleExpr>
<Assignment> -> <Variable> <ASSIGN> <Expr> <SC>
<Statement> -> <Assignment>
<StatementList> -> <StatementList> <Statement>
k
<Variable> -> <IDENTIFIER>
<Constant> -> <INTCON> 3
<Factor> -> <Constant>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
<Expr> -> <SimpleExpr>
<Assignment> -> <Variable> <ASSIGN> <Expr> <SC>
<Statement> -> <Assignment>
<StatementList> -> <StatementList> <Statement>
l
<Variable> -> <IDENTIFIER>
<Constant> -> <INTCON> 4
<Factor> -> <Constant>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
<Expr> -> <SimpleExpr>
<Assignment> -> <Variable> <ASSIGN> <Expr> <SC>
<Statement> -> <Assignment>
<StatementList> -> <StatementList> <Statement>
j
<Variable> -> <IDENTIFIER>
i
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
k
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <MulExpr> <TIMES> <Factor> 
l
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <MulExpr> <TIMES> <Factor> 
<SimpleExpr> -> <AddExpr>
<Expr> -> <SimpleExpr>
<Assignment> -> <Variable> <ASSIGN> <Expr> <SC>
<Statement> -> <Assignment>
<StatementList> -> <StatementList> <Statement>
j
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
<Expr> -> <SimpleExpr>
84
<IOStatement> -> <WRITE> <LP> <Expr> <RP> <SC>   84
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
<ProcedureBody> -> <StatementList> <RBR>
<ProcedureDecl> -> <ProcedureHead> <ProcedureBody>
<Procedures> -> epsilon
<Procedures> -> <ProcedureDecl> <Procedures>
<Program> -> <DeclList> <Procedures>
