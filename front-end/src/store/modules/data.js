const state = {
    used: false,
    version: 2,
    date_modified: 0,
    data: {
        selectedSc: [],
        selectedSCInfor: [],
        initialMarkingInfor: {
          NumberOfUser: null,
          Balance:{
            type: "fixed",
            fixed: null,
            random: {from: null, to: null},
            map: null
            },
          Funtion_params: {}
        },      
        selectedContext: {used:false,data:{}},
        selectedVulnerbility: {type:"",params:{}},
    },
    views: {
        checking_road_view: 1,
    }
  }
  
  const getters = {
    /* -- data -- */
    GetSelectedSC: state => {
      return state.data.selectedSc;
    },
    GetSCSelectedInfor: state => {
      return state.data.selectedSCInfor
    },
    GetSelectedContext: state => {
      return state.data.selectedContext;
    },
    GetSelectedVulnerbility: state => {
      return state.data.selectedVulnerbility;
    },
    GetInitialMarking: state => {
      return state.data.initialMarkingInfor;
    },
    /* -- view -- */
    GetCheckingRoadView: (state) => state.views.checking_road_view,
  }

  const mutations = {
      /* -- used */
    SetUsedState(state,value){
        state.used = value
    },
    SetDateState(state,value){
        state.date_modified = value
    },
      /* -- data -- */
    SetDataState(state,data){
        state.data = data
    },
    SetSelectedSC(state, newArr) {
      state.data.selectedSc = newArr;
    },
    SetSelectedContext(state, newArr){
      state.data.selectedContext.used = true
      state.data.selectedContext.data = newArr;
    },
    SetSelectedVulnerbility(state, newArr){
      state.data.selectedVulnerbility = newArr;
    },
    SetSCSelectedInfo(state, newArr){
      state.data.selectedSCInfor = newArr;
    },
    SetInitialMarking(state, new_initial_data){
      state.data.initialMarkingInfor = new_initial_data
    },
    /* -- view -- */
    SetViewsState(state,views){
        state.views = views
    },
    SetCheckingRoadView(state, road_view){
        state.views.checking_road_view = road_view
    },
    /* ---- set all data ---- */
    SetAllData(state,value){
      state.date_modified = value.date_modified
      state.views = value.views
      state.data = value.data
    }
  }
  
  export default {
      namespaced: true,
      state: state,
      getters: getters,
      mutations: mutations,
  }