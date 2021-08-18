const state = {
    used: false,
    version: 2,
    date_modified: 0,
    data: {
        selectedSc: [],
        selectedSCInfor: {},
        selectedContext: [],
        selectedVulnerbility: [],
    },
    views: {
        process: 'sc-selection',
        road_page: 1,
        current_page: 1,
        fourth_step_views_list: [{name:"property-coptions"}],
        fourth_step_views: "property-coptions",
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
    
    /* -- view -- */
    GetProcessView: (state) => state.views.process,
    GetRoadPage: (state) => state.views.road_page,
    GetCurrentPage: (state) => state.views.current_page,
    GetFourthStepViews: (state) => state.views.fourth_step_views,
    GetFourthStepViewsList: (state) => state.views.fourth_step_views_list,
  }
  
  const mutations = {
      /* -- used */
    SetUsedState(state,value){
        state.used = value
    },
    SetDateState(state,value){
        state.date_modified = value
    },
    ResetState(state){
        state.used = false
        state.data = {
            selectedSc: [],
            selectedSCInfor: {},
            selectedContext: [],
            selectedVulnerbility: [],
        }
        state.views = {
          process: 'sc-selection',
          road_page: 1,
          current_page: 1,
          fourth_step_views_list: [{name:"property-coptions"}],
          fourth_step_views: "property-coptions",
        }
    },
      /* -- data -- */
    SetDataState(state,data){
        state.data = data
    },
    SetSelectedSC(state, newArr) {
      state.data.selectedSc = newArr;
    },
    SetSelectedContext(state, newArr){
      state.data.selectedContext = newArr;
    },
    SetSelectedVulnerbility(state, newArr){
      state.data.selectedVulnerbility = newArr;
    },
    SetSCSelectedInfo(state, newArr){
      state.data.selectedSCInfor = newArr;
    },
    NewSCSelectedInfor(state, newkey) {
      state.data.selectedSCInfor[newkey] = {list_gvs: [],list_lvs: {}}
    },
    RemoveSCSelectedInfor(state, expriedkey) {
      delete state.data.selectedSCInfor[expriedkey];
    },
    addGVSInfor(state, {id, data}){
      state.data.selectedSCInfor[id].list_gvs = data
    },
    addLVSInfor(state, {id, data}){
      state.data.selectedSCInfor[id].list_lvs = data
    },

    /* -- view -- */
    SetViewsState(state,views){
        state.views = views
    },
    SetProcessView(state, processviews) {
        state.views.process = processviews;
    },
    SetRoadPage(state, road_page){
        state.views.road_page = road_page
    },
    SetCurrentPage(state, current_page){
        state.views.current_page = current_page
    },
    SetFourthStepViews(state, value){
      state.views.fourth_step_views = value
    },
    SetFourthStepViewsList(state, value){
      state.views.fourth_step_views_list = value
    },
    UpdateFourthStepViewsList(state, value){
      state.views.fourth_step_views_list.push(value)
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