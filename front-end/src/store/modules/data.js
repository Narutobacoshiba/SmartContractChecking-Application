const state = {
    used: false,
    version: 2,
    date_modified: 0,
    data: {
        selectedSc: [],
        selectedSCInfor: {},
        selectedContext: [],
        selectedVulnerbility: [],
        configVul: {id: 1}
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
    GetConfigVul: state => {
      return state.data.configVul;
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
            configVul: {}
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
    NewSCSelectedInfor(state, {sc_id, sc_info}) {
      var vuls = state.data.selectedVulnerbility
      var list_gvs = sc_info.list_gvs
      var list_funcs = sc_info.list_functions
      var list_lvs = {}
      for(let i = 0; i < list_funcs.length; i ++){
        var lvs = list_funcs[i].list_lvs
        var name = list_funcs[i].name
        list_lvs[name] = lvs
      }
      
      if(vuls.length > 0){
        var obj = {}
        if(state.data.selectedSCInfor[sc_id]) obj = state.data.selectedSCInfor[sc_id];
        var info = {list_gvs: list_gvs, list_lvs: list_lvs}
        for(let i = 0; i< vuls.length; i++){
          var vid = vuls[i].id
          if(!(vid in obj)){
            obj[vid] = info
        }
        }
        state.data.selectedSCInfor[sc_id] = obj
      }else{
        state.data.selectedSCInfor[sc_id] = {}
      }
      console.log(state.data.selectedSCInfor)
    },
    RemoveSCSelectedInfor(state, expriedkey) {
      delete state.data.selectedSCInfor[expriedkey];
    },
    addGVSInfor(state, {vul_id, sc_id, data}){
      state.data.selectedSCInfor[sc_id][vul_id].list_gvs = data
    },
    addLVSInfor(state, {sc_id,vul_id, func_name, data}){
      state.data.selectedSCInfor[sc_id][vul_id].list_lvs[func_name] = data
    },
    SetConfigVul(state, vul){
      state.data.configVul = vul
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