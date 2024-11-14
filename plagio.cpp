#include <iostream>
#include "../Lab16/exp.h"
#include "../Lab16/visitor.h"
#include <unordered_map>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////
// Métodos accept
int BinaryExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int IFExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int NumberExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int BoolExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int IdentifierExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int AssignStatement::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int PrintStatement::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int IfStatement::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int WhileStatement::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int ForStatement::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int VarDec::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int VarDecList::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int StatementList::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int Body::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int ReturnStatement::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int Program::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int FunDec::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int FunDecList::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int FCallExp::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////
// Métodos visit del PrintVisitor

int PrintVisitor::visit(FCallExp* exp) {
    cout << exp->functionName << "(";
    bool first = true;
    for (Exp* arg : exp->args) {
        if (!first) cout << ", ";
        arg->accept(this);
        first = false;
    }
    cout << ")";
    return 0;
}

int PrintVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    cout << ' ' << Exp::binopToChar(exp->op) << ' ';
    exp->right->accept(this);
    return 0;
}

int PrintVisitor::visit(NumberExp* exp) {
    cout << exp->value;
    return 0;
}

int PrintVisitor::visit(BoolExp* exp) {
    if (exp->value) cout << "true";
    else cout << "false";
    return 0;
}

int PrintVisitor::visit(IdentifierExp* exp) {
    cout << exp->name;
    return 0;
}

void PrintVisitor::visit(AssignStatement* stm) {
    cout << stm->id << " = ";
    stm->rhs->accept(this);
    cout << ";";
}

void PrintVisitor::visit(PrintStatement* stm) {
    cout << "print(";
    stm->e->accept(this);
    cout << ");";
}

void PrintVisitor::visit(IfStatement* stm) {
    cout << "if ";
    stm->condition->accept(this);
    cout << " then" << endl;
    stm->then->accept(this);
    if (stm->els) {
        printIndent();
        cout << "else" << endl;
        stm->els->accept(this);
    }
    printIndent();
    cout << "endif";
}

void PrintVisitor::imprimir(Program* program) {
    program->accept(this);
}

int PrintVisitor::visit(IFExp* pepito) {
    cout << "ifexp(";
    pepito->cond->accept(this);
    cout << ",";
    pepito->left->accept(this);
    cout << ",";
    pepito->right->accept(this);
    cout << ")";
    return 0;
}

void PrintVisitor::visit(WhileStatement* stm) {
    cout << "while ";
    stm->condition->accept(this);
    cout << " do" << endl;
    stm->b->accept(this);
    printIndent();
    cout << "endwhile";
}

void PrintVisitor::visit(ForStatement* stm) {
    cout << "for ";
    stm->start->accept(this);
    cout << " to ";
    stm->end->accept(this);
    cout << " step ";
    stm->step->accept(this);
    cout << " do" << endl;
    stm->b->accept(this);
    printIndent();
    cout << "endfor";
}

void PrintVisitor::visit(VarDec* stm) {
    cout << "var " << stm->type << " ";
    for (auto i : stm->vars) {
        cout << i;
        if (i != stm->vars.back()) cout << ", ";
    }
    cout << ";";
}

void PrintVisitor::visit(VarDecList* stm) {
    for (auto i : stm->vardecs) {
        printIndent();
        i->accept(this);
        cout << endl;
    }
}

void PrintVisitor::visit(StatementList* stm) {
    for (auto i : stm->stms) {
        printIndent();
        i->accept(this);
        cout << endl;
    }
}

void PrintVisitor::visit(Body* stm) {
    increaseIndent();
    if (stm->vardecs) stm->vardecs->accept(this);
    if (stm->slist) stm->slist->accept(this);
    decreaseIndent();
}

void PrintVisitor::printIndent() {
    for (int i = 0; i < indentLevel * 2; i++) {
        cout << ' ';
    }
}

void PrintVisitor::visit(FunDec* func) {

    cout << "fun " << func->type << " " << func->id << "(";
    if (func->params) {
        bool first = true;
        for (const auto& param : func->params->type) {
            if (!first) cout << ", ";
            cout << param.first << " " << param.second;
            first = false;
        }
    }
    cout << ")" << endl;

    func->body->accept(this);
    printIndent();
    cout << "endfun" << endl;
}


void PrintVisitor::visit(FunDecList* funDecList) {
    for (FunDec* func : funDecList->functions) {
        func->accept(this);
        cout << endl;
    }
}

int PrintVisitor::visit(ReturnStatement* stm) {
    cout << "return ";
    if (stm->returnExp) {
        stm->returnExp->accept(this);
    }
    cout << ";";
    return 0;
}

int PrintVisitor::visit(Program* program) {
    program->varDecList->accept(this);
    cout << endl;
    program->funDecList->accept(this);
    return 0;
}
