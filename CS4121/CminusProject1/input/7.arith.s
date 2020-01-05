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
<DeclList> -> <Type> <IdentifierList> <SC>
<Type> -> <INTEGER>
<FunctionDecl> ->  <Type> <IDENTIFIER> <LP> <RP> <LBR>
<ProcedureHead> -> <FunctionDecl>
i
<Variable> -> <IDENTIFIER>
<Constant> -> <INTCON> 1
<Factor> -> <Constant>
<MulExpr> -> <Factor>
<SimpleExpr> -> <AddExpr>
<Expr> -> <SimpleExpr>
<Assignment> -> <Variable> <ASSIGN> <Expr> <SC>
<Statement> -> <Assignment>
<StatementList> -> <Statement>
j
<Variable> -> <IDENTIFIER>
<Constant> -> <INTCON> 2
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
i
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
j
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<AddExpr> -> <AddExpr>1 <PLUS> <MulExpr>2 
k
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
l
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <MulExpr> <TIMES> <Factor> 
<AddExpr> -> <AddExpr>3 <PLUS> <MulExpr>12 
<SimpleExpr> -> <AddExpr>
<Expr> -> <SimpleExpr>
15
<IOStatement> -> <WRITE> <LP> <Expr> <RP> <SC>   15
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
i
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
l
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
i
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<AddExpr> -> <AddExpr> <MINUS> <MulExpr> 
<SimpleExpr> -> <AddExpr>
<Expr> -> <SimpleExpr>
<Factor> -> <LP> <Expr> <RP>
<MulExpr> -> <Factor>
k
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <MulExpr> <DIVIDE> <Factor> 
<AddExpr> -> <AddExpr>1 <PLUS> <MulExpr>1 
j
<Variable> -> <IDENTIFIER>
<Factor> -> <Variable>
<MulExpr> -> <Factor>
<AddExpr> -> <AddExpr>2 <PLUS> <MulExpr>2 
<SimpleExpr> -> <AddExpr>
<Expr> -> <SimpleExpr>
4
<IOStatement> -> <WRITE> <LP> <Expr> <RP> <SC>   4
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
<ProcedureBody> -> <StatementList> <RBR>
<ProcedureDecl> -> <ProcedureHead> <ProcedureBody>
<Procedures> -> epsilon
<Procedures> -> <ProcedureDecl> <Procedures>
<Program> -> <DeclList> <Procedures>
