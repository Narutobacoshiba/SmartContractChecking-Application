export default {
    SET_LIST_POSTS(state, data) {
        state.listTransaction = data;
    },
    PUSH_LIST_POSTS(state, data) {
        state.listTransaction = [...state.listTransaction, ...data];
    },
    SET_ID(state, data){
        console.log("mutation setid");
        state.id = data;
    },
    SET_LIST_CHECK(state, data){
        state.listCheck = data;
    },
    SET_LIST_SMART_CONTRACT(state,data){
        state.listSmartContract = data;
    }
}