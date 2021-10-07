import Axios from "axios";

export default {
    async getListTran({ commit }) {
        try {
            var result = await Axios.get('http://127.0.0.1:8000/select-sc/listofcheckedtransactions/');
            commit('SET_LIST_POSTS',result.data)
            if(result.data.status === 200) {
                commit('SET_LIST_POSTS',result.data)
            }
        } catch(error) {
            console.log("error", error);
        }
    },

}