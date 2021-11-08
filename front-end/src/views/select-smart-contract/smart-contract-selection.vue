<template>
    <div>
        <div id="view-scs-name">
            <p>Select Smart Contract</p>
        </div>
        <div id="ams-body">
            <!-- <div id="amsb-header">
                <p>Add Smart Contracts</p>
                <div id="bheader-action">
                    <div id="bheader-a-cancle" @click="CancelSLSc">
                        <div class="bheader-icon-holder"><span class="material-icons bheader-icon" id="bheader-rm-icon">remove</span></div>
                        <div class="bheader-action-label">Cancel</div>
                        </div>
                        <div id="bheader-a-update" @click="SaveSLSc">
                            <div class="bheader-icon-holder"><span class="material-icons bheader-icon" id="bheader-add-icon">add</span></div>
                            <div class="bheader-action-label">Update selection</div>
                        </div>
                    <div></div>
                </div>
            </div> -->
            <div id="amsb-functional">
                <div id="hfun-f-search">
                        <span class="material-icons" id="fsearch-icon" @click="filterByName()">search</span>
                        <input type="text" @keyup.enter="filterByName()" v-model="name_input" placeholder="Search smart contract name" id="fsearch-input" />
                    </div>
                <div id="hfun-filter">
                    <div class="hfun-f-selectbox">
                        <div>Type</div>
                            <select v-model="type_selection">
                                <option value="any">any</option>
                                <option value="common">common</option>
                                <option value="private">private</option>
                            </select>
                    </div>
                    <div class="hfun-f-selectbox">
                        <div>Status</div>
                            <select v-model="selected_selection">
                                <option value="any">any</option>
                                <option value="selected">selected</option>
                                <option value="unselected">unselected</option>
                            </select>
                    </div>
                </div>
            </div>
            <div id="amsb-table">
                <div id="table-header">
                    <div class="name-cell table-cell" @click="sortBy('name')">
                        <div>Name</div>
                        <span v-if="sort_asc['name']==1" class="material-icons sort-icon" :class="{unselect_icon: sort_selection != 'name'}">arrow_drop_up</span>
                        <span v-if="sort_asc['name']==-1" class="material-icons sort-icon" :class="{unselect_icon: sort_selection != 'name'}">arrow_drop_down</span>
                    </div>
                    <div class="type-cell table-cell" @click="sortBy('type')">
                        <div>Type</div>
                        <span v-if="sort_asc['type']==1" class="material-icons sort-icon" :class="{unselect_icon: sort_selection != 'type'}">arrow_drop_up</span>
                        <span v-if="sort_asc['type']==-1" class="material-icons sort-icon" :class="{unselect_icon: sort_selection != 'type'}">arrow_drop_down</span>
                    </div>
                    <div class="lastupdate-cell table-cell" @click="sortBy('date_modified')"> 
                        <div>Last update</div>
                        <span v-if="sort_asc['date_modified']==1" class="material-icons sort-icon" :class="{unselect_icon: sort_selection != 'date_modified'}">arrow_drop_up</span>
                        <span v-if="sort_asc['date_modified']==-1" class="material-icons sort-icon" :class="{unselect_icon: sort_selection != 'date_modified'}">arrow_drop_down</span>
                    </div>
                    <div class="select-cell table-cell">
                        <div v-if="isChangeSelect == false">Select</div>
                        <button v-else class="button-style" id="update-select-button" @click="updateSelection">Update</button>
                    </div>
                </div>
                <div id="table-body" v-if="list_sc_length > 0">
                    <div v-for="(sc,idx) in getShowList" :key="idx" class="table-row" :class="{row_even: idx%2 == 0, row_odd: idx%2 == 1}">
                            <div class="name-cell table-cell">
                                {{sc.name}}
                            </div>
                            <div class="type-cell table-cell">
                                {{sc.type}}
                            </div>
                            <div class="lastupdate-cell table-cell">
                                {{convertDate(sc.date_modified)}}
                            </div>
                            <div class="select-cell table-cell">
                                <input type="checkbox" :value="sc" v-model="selected_sc" />
                            </div>
                    </div>
                </div>
                <div v-else class="table-row-error">
                    <p>{{error_handler}}</p>
                </div>
            </div>
            <div id="amsb-footer">
                <div id="itb-entries">
                    Show {{numOfRecod}}/{{numOfItems}} entries
                </div>
                <div id="itb-cnpage">
                    <i class="material-icons" id="itb-first-page-icon" @click="goPage(1)">first_page</i>
                    <i class="material-icons" id="itb-pre-page-icon" @click="goPage(pageNum > 1 ? (pageNum-1):1)">chevron_left</i>
                    <div id="itb-cnpage-count" >{{countPageNum}}</div>
                    <i class="material-icons" id="itb-next-page-icon" @click="goPage(pageNum < num_of_page ? (pageNum+1):num_of_page)">chevron_right</i>
                    <i class="material-icons" id="itb-last-page-icon" @click="goPage(num_of_page)">last_page</i>
                </div>
            </div>
        </div>
        <div id="ssc-button">
            <button class="button-style" role="button" @click="goNextPage">Next</button>
            <button class="button-style" role="button" >Upload Smart Contract File</button>
            <button class="button-style" role="button" @click="goPrePage">Back</button>
        </div>
    </div>
</template>

<script>
import { SmartContractService } from "../../services/smartcontract.services.js";
export default ({
    data(){
        return{
            pre_selected_sc: [],
            selected_sc: [],
            list_sc: [],
            filtername_items: [],
            selection_items: [],

            num_of_record: 6,
            num_of_page: 0,
            pageNum: 1,

            type_selection: "any",
            selected_selection: "any",

            sort_selection: "type",
            sort_asc: {name:1,type:1,date_modified:1},

            name_input: "",
            error_handler: "",
        }
    },
    mounted(){
        this.getSmartContract()
    },
    watch: {
        type_selection: function(){
            this.filterListItems()
        },
        selected_selection: function(){
            this.filterListItems()
        },
        sort_selection: function(val){
            this.sortItems(val)
        }
    },
    computed: {
        list_sc_length(){
            return this.list_sc.length
        },
        getShowList(){
            let ret = []
            for(let i = 0; i<this.selection_items.length; i++){
                if(((this.pageNum-1)*this.num_of_record <= i) && (this.pageNum*this.num_of_record > i)){
                    ret.push(this.selection_items[i])
                }
            }
            return ret
        },
        countPageNum(){
            return ""+this.pageNum+"/"+this.num_of_page
        },
        numOfItems(){
            return this.selection_items.length
        },
        numOfRecod(){
            if(this.selection_items.length < this.num_of_record*this.pageNum){
                return this.selection_items.length-this.num_of_record*(this.pageNum-1)
            }
            return this.num_of_record
        },
        isChangeSelect(){
            return this.selected_sc != this.pre_selected_sc
        }
    },
    methods: {
        async getSmartContract () {
            try {
                let response = await SmartContractService.getAllSmartContract()
                
                this.list_sc = response.data   
                this.selected_sc = this.$store.getters["data/GetSelectedSC"];
                this.pre_selected_sc = this.selected_sc
                this.filtername_items = this.list_sc
                
                this.filterListItems()
                this.sortItems(this.sort_selection)      
            } catch (error) {
                this.list_sc = []
                this.error_handler = error.detail
            }
        },
        filterByName(){
            if(this.name_input != '')
            {
                this.filtername_items = this.list_sc.filter(el => (el.name.startsWith(this.name_input)))
            }else{
                this.filtername_items = this.list_sc
            }
            this.filterListItems()
        },
        filterListItems(){
            var first_sort = this.filterBySelected(this.filtername_items)
            this.selection_items = this.filterByType(first_sort)

            this.num_of_page = Math.ceil(this.selection_items.length/this.num_of_record)
            this.num_of_page = (this.num_of_page == 0 ? 1:this.num_of_page)
            this.pageNum = 1
        },
        filterByType(list){
            if(this.type_selection != 'any'){
                return list.filter(el => (el.type == this.type_selection))
            }
            return list
        },
        filterBySelected(list){
            if(this.selected_selection == 'selected'){
                return this.selected_sc
            }
            if(this.selected_selection == 'unselected'){
                return this.getUnSelectedSc(list)
            }
            return list
        },
        sortItems(value){
            this.selection_items.sort((a,b) => (a[value] > b[value]) ? this.sort_asc[value] : ((b[value] > a[value]) ? -this.sort_asc[value] : 0))
        },
        sortBy(value){
            if(this.sort_selection == value){
                this.sort_asc[value] *= -1
                this.sortItems(value)
            }
            else{
                this.sort_selection = value
            }
        },
        getUnSelectedSc(list){
            let map = {}
            this.selected_sc.forEach(i => map[i.id] = false)
            let ret = []
            for(let i=0; i<list.length; i++){
                if(!(list[i].id in map)){
                    ret.push(list[i])
                }
            }
            return ret
        },
        convertDate(value){
            var date = new Date(value)
            var datestring = ""+date.getDate()
            var monthstring = ""+(date.getMonth()+1)
            var hourstring = ""+date.getHours()
            var minutestring = ""+date.getMinutes()
            hourstring = (hourstring.length == 1 ? '0'+hourstring:hourstring)
            minutestring = (minutestring.length == 1 ? '0'+minutestring:minutestring)
            datestring = (datestring.length == 1 ? '0'+datestring:datestring)
            monthstring = (monthstring.length == 1 ? '0'+monthstring:monthstring)
            return datestring+"/"+monthstring+"/"+date.getFullYear()+" "+hourstring+":"+minutestring
        },
        async updateSelection(){
            let cur_map = {}
            let list_expr_sc = {}
            this.selected_sc.forEach(i => cur_map[i.id] = false) 
            for(let i=0; i<this.pre_selected_sc.length; i++){
                if(!(this.pre_selected_sc[i].id in cur_map)){
                    list_expr_sc[this.pre_selected_sc[i].id] = false
                }
            }
            let sc_infor = this.$store.getters["data/GetSCSelectedInfor"]
            let count = 0;
            while (count < sc_infor.length) {
                if (sc_infor[count].id in list_expr_sc) {
                    sc_infor.splice(count, 1)
                } else {
                    ++count
                }
            }

            let pre_map = {}    
            let list_new_sc = []
            this.pre_selected_sc.forEach(i => pre_map[i.id] = false) 
            for(let i=0; i<this.selected_sc.length; i++){
                if(!(this.selected_sc[i].id in pre_map)){
                    list_new_sc.push(this.selected_sc[i].id)
                }
            }
            let data = []
            try{
                let response = await SmartContractService.getSmartContractInformation(list_new_sc)
                data = response.data
            }catch(error){
                console.log(error)
            }
            
            for(let i=0; i<data.length; i++){
                sc_infor.push(data[i])
            }

            this.$store.commit("data/SetSCSelectedInfo",sc_infor)
            this.$store.commit("data/SetSelectedSC", this.selected_sc);
            this.pre_selected_sc = this.selected_sc
        },
        goNextPage(){
            this.$router.push({ name: "ContextSelection" });
        },
        goPrePage(){
            this.$router.push({ name: "ContextSelection" });
        }
    }
})
</script>

<style scoped>
#view-scs-name{
    text-align: center;
    font-size: 30px;
    font-weight: bold;
    margin-top: 20px;
    margin-bottom: 20px;
}

#ams-body{
    width: 80%;
    height: 440px;
    margin: auto;
    min-width: 900px;
    background-color: white;
    border-radius: 4px;
    border: 4px solid rgb(207, 207, 207);
}

/* ---- amsb-header ---- */
#amsb-header{
    width: 100%;
    height: 40px;
    background-color: #435d7d;
    display: flex;
    border-top-right-radius: 4px;
    border-top-left-radius: 4px;
}
#amsb-header p{
    font-size: 16px;
    font-weight: bold;
    color: white;
    margin-top: 8px;
    margin-left: 10px;
}
#bheader-action{
    width: 260px;
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-left: auto;
    order: 2;
}
#bheader-a-cancle{
    display: flex;
    align-items: center;
    justify-content: center;
    height: 25px;
    width: 100px;

    background-color: #c55651;
    cursor: pointer;
}
#bheader-a-update{
    display: flex;
    align-items: center;
    justify-content: center;
    height: 25px;
    width: 150px;

    background-color: #449d44;
    cursor: pointer;
}
.bheader-action-label{
    font-size: 14px;
    color: white;
}
.bheader-icon-holder{
    width: 15px;
    height: 15px;
    margin-right: 5px;
    border-radius: 50%;
    background-color: white;

    display: flex;
    align-items: center;
    justify-content: center;
}
.bheader-icon{
    font-size: 11px;
}
#bheader-rm-icon{
    color: #c55651;
}
#bheader-add-icon{
    color: #449d44;
}
/* ---- amsb-functional ---- */
#amsb-functional{
    width: 96%;
    height: 50px;
    margin: 0 auto;
    display: flex;
}

#hfun-filter{
    display: flex;
    align-items: center;
    margin-left: auto;
    order: 2;
}

#hfun-f-search{
    display: flex;
    align-items: center;
    margin-top: 10px;
    height: 30px;
    width: 240px;
    border: 1px solid #535353;
    border-radius: 4px;
}
#fsearch-icon{
    font-size: 23px;
    color: #8b8a8a;
    margin-left: 2px;
    cursor: pointer;
}
#fsearch-icon:hover{
    color: #6b6a6a;
}
#fsearch-input{
    width: 200px;
    height: 20px;
    border: none;
    color: #575656;
}
#fsearch-input:focus {
    outline: none;
}

.hfun-f-selectbox{
    display: flex;
    align-items: center;
    margin-left: 15px;
}
.hfun-f-selectbox div{
    font-size: 14px;
    margin-right: 5px;
    color: #575656;
}
.hfun-f-selectbox select{
    height: 25px;
    width: 120px;
    background-color: white;
    border: none;
    border-radius: 3px;
    box-shadow: 0 1px 2px 0 rgba(0,0,0,0.37);
    color: #575656;
}
/* ---- amsb-talbe ---- */
#amsb-table{
    height: 340px;
    width: 96%;
    margin: 0 auto;
}

#table-header{
    width: 100%;
    height: 40px;
    border-top: 2px solid #dddcdc;
    display: flex;
    justify-content: space-between;
    align-items: center;
    font-weight: bold;
    color: black;
}
#table-header div:hover span{
    visibility: unset;
}
.sort-icon{
    color: rgb(114, 165, 55);
    cursor: pointer;
}
.unselect_icon{
     visibility: hidden;
}
#table-body{
    width: 100%;
    height: 300px;
}
.table-row{
    width: 100%;
    height: 50px;
    display: flex;
    align-items: center;
    color: rgb(68, 67, 67);
    border-top: 2px solid #dddcdc;
}
.table-row:hover{
    background-color: #f5f5f5;
}
.row_even{
    background-color: #fcfcfc;
}
.row_odd{
    background-color: white;
}
.name-cell{
    flex-basis: 45%;
    margin-left: 10px;
}
.type-cell{
    flex-basis: 20%;
}
.lastupdate-cell{
    flex-basis: 25%;
}
.select-cell{
    flex-basis: 10%;
    justify-content: center;
}
.table-cell{
    display: flex;
    height: 28px;
    overflow: hidden;
    text-overflow: ellipsis;
}

#update-select-button{
    font-size: 12px;
    display: flex;
    align-items: center;
    height: 24px;
}
/* ---- amsb-footer ---- */
#amsb-footer{
    width: 100%;
    height: 50px;
    border-bottom-right-radius: 4px;
    border-bottom-left-radius: 4px;
    display: flex;
}

#itb-entries{
    font-size: 14px;
    margin-top: 10px;
    margin-left: 2%;
}
#itb-cnpage{
    margin-left: auto;
    order: 2;
    margin-top:10px;
    margin-right: 2%;
    display: flex;
}

#itb-cnpage i {
    margin-top: 1px;
    font-size: 22px;
    color: #636262;
    cursor: pointer;
}
#itb-cnpage i:hover{
    color: #424141;
}

/* Button */
#ssc-button{
    width: 70%;
    height: 80px;
    margin: auto;
    margin-top: 20px;
    display: flex;
    justify-content: space-between;
    align-items: center;
}
.button-style {
  background-color: #FFFFFF;
  border: 0;
  border-radius: .5rem;
  box-sizing: border-box;
  color: #111827;
  font-family: "Inter var",ui-sans-serif,system-ui,-apple-system,system-ui,"Segoe UI",Roboto,"Helvetica Neue",Arial,"Noto Sans",sans-serif,"Apple Color Emoji","Segoe UI Emoji","Segoe UI Symbol","Noto Color Emoji";
  font-size: .875rem;
  font-weight: 600;
  line-height: 1.25rem;
  padding: .75rem 1rem;
  text-align: center;
  text-decoration: none #D1D5DB solid;
  text-decoration-thickness: auto;
  box-shadow: 0 2px 4px 0 rgba(0, 0, 0, 0.1), 0 2px 3px 0 rgba(0, 0, 0, 0.06);
  cursor: pointer;
  user-select: none;
  -webkit-user-select: none;
  touch-action: manipulation;
}

.button-style:hover {
  background-color: rgb(249,250,251);
}

.button-style:focus {
  outline: 2px solid transparent;
  outline-offset: 2px;
}

.button-style:focus-visible {
  box-shadow: none;
}
</style>
