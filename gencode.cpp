#include "gencode.hh"

ImpValue BinaryExp::accept(ImpValueVisitor* v) {
    return v->visit(this);
}

ImpValue BoolExp::accept(ImpValueVisitor* v) {
    return v->visit(this);
}

ImpValue NumberExp::accept(ImpValueVisitor* v) {
    return v->visit(this);
}

ImpValue IdentifierExp::accept(ImpValueVisitor* v) {
    return v->visit(this);
}


ImpValue IFExp::accept(ImpValueVisitor* v) {
    return v->visit(this);
}



void AssignStatement::accept(ImpValueVisitor* v) {
    return v->visit(this);
}

void PrintStatement::accept(ImpValueVisitor* v) {
    return v->visit(this);
}

void IfStatement::accept(ImpValueVisitor* v) {
    return v->visit(this);
}

void WhileStatement::accept(ImpValueVisitor* v) {
    return v->visit(this);
}


void ForStatement::accept(ImpValueVisitor* v) {
    return v->visit(this);
}


void StatementList::accept(ImpValueVisitor* v) {
    return v->visit(this);
}

void VarDec::accept(ImpValueVisitor* v) {
    return v->visit(this);
}


void VarDecList::accept(ImpValueVisitor* v) {
    return v->visit(this);
}



void Body::accept(ImpValueVisitor* v) {
    return v->visit(this);
}

void Program::accept(ImpValueVisitor* v) {
    return v->visit(this);
}

void ImpCODE::interpret(Program* p) {
    env.clear();
    p->accept(this);
    return;
}



void ImpCODE::visit(Program* p) {
    env.add_level();
    p->body->accept(this);
}

void ImpCODE::visit(Body* b) {
    env.add_level();
    b->vardecs->accept(this);
    b->slist->accept(this);
    env.remove_level();
    return;
}

void ImpCODE::visit(VarDecList* decs) {
    list<VarDec*>::iterator it;
    for (it = decs->vardecs.begin(); it != decs->vardecs.end(); ++it) {
        (*it)->accept(this);
    }
    return;
}


void ImpCODE::visit(VarDec* vd) {
    list<string>::iterator it;
    ImpValue v;
    ImpVType tt = ImpValue::get_basic_type(vd->type);
    v.set_default_value(tt);
    for (it = vd->vars.begin(); it != vd->vars.end(); ++it) {
        env.add_var(*it, v);
    }
    return;
}



void ImpCODE::visit(StatementList* s) {
    list<Stm*>::iterator it;
    for (it = s->stms.begin(); it != s->stms.end(); ++it) {
        (*it)->accept(this);
    }
    return;
}

void ImpCODE::visit(AssignStatement* s) {
    cout << "LDA " << s->id << endl ;
    ImpValue v = s->rhs->accept(this);
    ImpValue lhs = env.lookup(s->id);
    env.update(s->id, v);
    cout << "STOc"<< endl;
    return;
}

void ImpCODE::visit(PrintStatement* s) {
    ImpValue v = s->e->accept(this);
    cout << v << endl;
    return;
}

void ImpCODE::visit(IfStatement* s) {
    cout<<"inicio del if "<<endl;
    ImpValue  ex=  s->condition->accept(this);

    if (ex.bool_value==true){
        cout<<" Bloque then";
        s->then->accept(this);

    } else{
        cout<<" Bloque else";
        s->els->accept(this);
    }
    cout<<"fin del if "<<endl;

    return;
}

void ImpCODE::visit(WhileStatement* s) {
    cout << "L " << etiquetas << endl;
    ImpValue v = s->condition->accept(this);
    cout << "FJP " << etiquetas +1 << endl;
    s->b->accept(this);
    cout << "UJP "<<  etiquetas   << endl;
    cout << "L "<< etiquetas +1 << endl;
    etiquetas = etiquetas+1;
}


void ImpCODE::visit(ForStatement* s) {
    ImpValue v = ;
    cout<<"inicio del FOR "<<endl;
    cout<<"L "<< etiquetas<<endl;
    cout<<"inicio condicional"<<endl;
    int inicio=s->start->accept(this).int_value;
    int final=s->end->accept(this).int_value;
    int step=s->step->accept(this).int_value;
    cout<<"fin condicional"<<endl;
    cout<<"body"<<endl;
    cout<<"FJP "<<etiquetas+1<<endl;
    s->b->accept(this);
    s->b->accept(this);
    while (inicio<final){
        s->b->accept(this);
        inicio=inicio+step;
    }
    cout<<"UJP "<<etiquetas<<endl;
    cout<<"L "<< etiquetas+1<<endl;
    cout<<"fin del FOR "<<endl;




}





ImpValue ImpCODE::visit(BinaryExp* e) {
    ImpValue result;
    ImpValue v1 = e->left->accept(this);
    ImpValue v2 = e->right->accept(this);
    if (v1.type != TINT || v2.type != TINT) {
        cout << "Error de tipos: operandos en operacion binaria tienen que ser "
                "enteros"
             << endl;
        exit(0);
    }
    int iv, iv1, iv2;
    bool bv;
    ImpVType type = NOTYPE;
    iv1 = v1.int_value;
    iv2 = v2.int_value;
    switch (e->op) {
        case PLUS_OP:
            iv = iv1 + iv2;
            type = TINT;
            cout<< "ADI" << endl;
            break;
        case MINUS_OP:
            iv = iv1 - iv2;
            type = TINT;
            cout<< "SBI" << endl;
            break;
        case MUL_OP:
            iv = iv1 * iv2;
            type = TINT;
            cout<< "MPI" << endl;
            break;
        case DIV_OP:
            iv = iv1 / iv2;
            type = TINT;
            cout<< "DVI" << endl;
            break;
        case LT_OP:
            bv = (iv1 < iv2) ? 1 : 0;
            type = TBOOL;
            cout<< "LESc" << endl;
            break;
        case LE_OP:
            bv = (iv1 <= iv2) ? 1 : 0;
            type = TBOOL;
            cout<< "LEQc" << endl;
            break;
        case EQ_OP:
            bv = (iv1 == iv2) ? 1 : 0;
            type = TBOOL;
            cout<< "EQUc" << endl;
            break;
    }
    if (type == TINT)
        result.int_value = iv;
    else
        result.bool_value = bv;
    result.type = type;
    return result;
}

ImpValue ImpCODE::visit(NumberExp* e) {
    ImpValue v;
    v.set_default_value(TINT);
    v.int_value = e->value;
    cout << "LDCc " <<  e->value << endl;
    return v;
}

ImpValue ImpCODE::visit(BoolExp* e) {
    ImpValue v;
    v.set_default_value(TBOOL);
    v.int_value = e->value;
    return v;
}

ImpValue ImpCODE::visit(IdentifierExp* e) {
    if (env.check(e->name))
        cout << "LODc " << e->name <<endl;
        return env.lookup(e->name);
}

ImpValue ImpCODE::visit(IFExp* e) {
    cout<<"inicio IFe";
    ImpValue v = e->cond->accept(this);
    if (v.type != TBOOL) {
        cout << "Type error en ifexp: esperaba bool en condicional" << endl;
        exit(0);
    }
    if(v.bool_value){
        return e->left->accept(this);
    }
    else{
        return e->right->accept(this);
    }
}

