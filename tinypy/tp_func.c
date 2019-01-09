
tp_obj tpd_call(TP, tp_obj func(TP)) {
    return func(tp);
}

tp_obj tp_tcall(TP, tp_obj func) {
    if (func.type.magic & TP_FUNC_MASK_METHOD) {
        /* METHOD */
        tpd_list_insert(tp, tp->params.list.val, 0, func.func.info->self);
    }
    return tpd_call(tp,(tp_obj (*)(tp_vm *))func.func.cfnc);
}

tp_obj tp_func_nt(TP, int t, void *v, tp_obj c,tp_obj s, tp_obj g) {
    tp_obj r = {TP_FNC};
    tpd_func *info = (tpd_func*)tp_malloc(tp, sizeof(tpd_func));
    info->code = c;
    info->self = s;
    info->globals = g;
    r.type.magic = t;
    r.func.info = info;
    r.func.cfnc = v;
    return r;
}

tp_obj tp_func_t(TP, int t, void *v, tp_obj c, tp_obj s, tp_obj g) {
    return tp_track(tp, tp_func_nt(tp, t, v, c, s, g));
}

tp_obj tp_bind(TP, tp_obj function, tp_obj self) {
    return tp_func_t(tp,
                function.type.magic | TP_FUNC_MASK_METHOD,
                function.func.cfnc,
                function.func.info->code,
                self,
                function.func.info->globals);
}

tp_obj tp_def(TP, tp_obj code, tp_obj g) {
    return tp_func_t(tp,1,0,code,tp_None,g);
}

/* Function: tp_func
 * Creates a new tinypy function object.
 * 
 * This is how you can create a tinypy function object which, when called in
 * the script, calls the provided C function.
 */
tp_obj tp_function(TP, tp_obj v(TP)) {
    return tp_func_t(tp,0,v,tp_None,tp_None,tp_None);
}

tp_obj tp_method(TP,tp_obj self, tp_obj v(TP)) {
    return tp_func_t(tp,2,v,tp_None,self,tp_None);
}


