export default {
    SET_LIST_POSTS(state, data) {
        state.listTransaction = data;
    },
    PUSH_LIST_POSTS(state, data) {
        state.listTransaction = [...state.listTransaction, ...data];
    },
}