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
        selectedVulnerability: {type:"",subtype:"",params:{}},
        generateModelData: {
            generated: false,
            code: "",
            data: {}
        },
        checkingModelData: {
            checked: false,
            code: "",
            data: {}
        }
    },
    views: {
        checking_road_view: 1,
        current_road_view: 1,
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
    GetSelectedVulnerability: state => {
      return state.data.selectedVulnerability;
    },
    GetInitialMarking: state => {
      return state.data.initialMarkingInfor;
    },
    GetGenerateModelData: state => {
      return state.data.generateModelData;
    },
    GetCheckingModelData: state => {
      return state.data.checkingModelData;
    },
    /* -- view -- */
    GetCheckingRoadView: (state) => state.views.checking_road_view,
    GetCurrentRoadView: (state) => state.views.current_road_view,
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
    SetSelectedVulnerability(state, newArr){
      state.data.selectedVulnerability = newArr;
    },
    ResetSelectedVulnerability(state){
      state.data.selectedVulnerability = {type:"",subtype:"",params:{}};
    },
    SetSCSelectedInfo(state, newArr){
      state.data.selectedSCInfor = newArr;
    },
    SetInitialMarking(state, new_initial_data){
      state.data.initialMarkingInfor = new_initial_data
    },
    ResetInitialMarking(state){
      state.data.initialMarkingInfor = {
                                        NumberOfUser: null,
                                        Balance:{
                                          type: "fixed",
                                          fixed: null,
                                          random: {from: null, to: null},
                                          map: null
                                          },
                                        Funtion_params: {}
                                      }
    },
    SetGenerateModelData(state, new_generate_data){
      state.data.generateModelData = new_generate_data
    },
    ResetGenerateModelData(state){
      state.data.generateModelData = {
                                          generated: false,
                                          code: "",
                                          data: {}
                                      }
    },
    SetCheckingModelData(state, new_checking_data){
      state.data.checkingModelData = new_checking_data
    },
    ResetCheckingModelData(state){
      state.data.checkingModelData = {
                                          checked: false,
                                          code: "",
                                          data: {}
                                      }
    },
    /* -- view -- */
    SetViewsState(state,views){
        state.views = views
    },
    SetCheckingRoadView(state, road_view){
        state.views.checking_road_view = road_view
    },
    SetCurrentRoadView(state, road_view){
        state.views.current_road_view = road_view
    },
    /* ---- set all data ---- */
    ResetAllData(state){
      state.data =  {
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
                      selectedVulnerability: {type:"",subtype:"",params:{}},
                      generateModelData: {
                          generated: false,
                          code: "",
                          data: {}
                      },
                      checkingModelData: {
                          checked: false,
                          code: "",
                          data: {}
                      }
                    }
      state.views = {
                        checking_road_view: 1,
                    }
    }
  }
  
  export default {
      namespaced: true,
      state: state,
      getters: getters,
      mutations: mutations,
  }