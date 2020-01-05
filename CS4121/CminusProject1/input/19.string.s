<Type> -> <INTEGER>
<FunctionDecl> ->  <Type> <IDENTIFIER> <LP> <RP> <LBR>
<ProcedureHead> -> <FunctionDecl>
<StringConstant> -> <STRING>
"Your grader"<IOStatement> -> <WRITE> <LP> <StringConstant> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <Statement>
<StringConstant> -> <STRING>
"will put"<IOStatement> -> <WRITE> <LP> <StringConstant> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
<StringConstant> -> <STRING>
"a random"<IOStatement> -> <WRITE> <LP> <StringConstant> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
<StringConstant> -> <STRING>
"string here"<IOStatement> -> <WRITE> <LP> <StringConstant> <RP> <SC>
<Statement> -> <IOStatement>
<StatementList> -> <StatementList> <Statement>
<ProcedureBody> -> <StatementList> <RBR>
<ProcedureDecl> -> <ProcedureHead> <ProcedureBody>
<Procedures> -> epsilon
<Procedures> -> <ProcedureDecl> <Procedures>
<Program> -> <Procedures>
