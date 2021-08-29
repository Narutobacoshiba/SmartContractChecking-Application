<template>
    <div id="ams-body">
       <div id="amsb-header">
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
       </div>
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
                   <div>Select</div>
               </div>
           </div>
           <div id="table-body">
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
        <div id="showComponents" v-if="showConfirmation">
            <div id="components-holder">
            <confirm @cancel="cancelUpdate" @confirm="updateSCs" :dialog="dialog"/>
            </div>
         </div>
    </div>
</template>

<script>
import ConfirmationDialog from "../../../components/ConfirmationDialog.vue"
import { GetPrivateSmartContracts, GetCommonSmartContracts } from "../../../services/data.js";
export default ({
    components:{
        'confirm': ConfirmationDialog
    },
    data(){
        return{
            selected_sc: [],
            list_sc: [],
            filtername_items: [],
            selection_items: [],

            num_of_record: 7,
            num_of_page: 0,
            pageNum: 1,

            type_selection: "any",
            selected_selection: "any",

            sort_selection: "type",
            sort_asc: {name:1,type:1,date_modified:1},

            name_input: "",
            showConfirmation: false,
            dialog: {title: 'Update Smart Contracts', message: 'Are you sure to update your selection?', confirmbtn: 'Update'}
        }
    },
    mounted(){
        this.list_sc = GetPrivateSmartContracts().concat(GetCommonSmartContracts())
        this.selected_sc = this.$store.getters["data/GetSelectedSC"];
        this.filtername_items = this.list_sc

        this.filterListItems()
        this.sortItems(this.sort_selection)
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
        }
    },
    methods: {
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
        CancelSLSc(){
            this.$emit("closeComponents")
        },
        SaveSLSc(){
            this.showConfirmation = true
        },
        updateSCs(){
            var store_gvs = this.$store.state.data.data.selectedSCInfor;
            var new_update = this.selected_sc
            for (let idx = 0; idx < new_update.length; idx++) {
                if (!(new_update[idx].id in store_gvs)) {
                this.$store.commit(
                    "data/NewSCSelectedInfor",
                    new_update[idx].id
                    );
                }
            }
            this.$store.commit("data/SetSelectedSC", new_update);
            this.$store.commit("views/SetHomeView", "sc-selection");
            this.CancelSLSc()
        },
        cancelUpdate(){
            this.showConfirmation = false
        },
        goPage(value){
            this.pageNum = value
        }
    }
})
</script>

<style scoped>
#ams-body{
    width: 1000px;
    height: 600px;

    background-color: white;
    border-radius: 4px;
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
    background-color: white;
    border: none;
    border-radius: 3px;
    box-shadow: 0 1px 2px 0 rgba(0,0,0,0.37);
    color: #575656;
}
/* ---- amsb-talbe ---- */
#amsb-table{
    height: 460px;
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
    height: 420px;
}
.table-row{
    width: 100%;
    height: 60px;
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
    height: 24px;
    overflow: hidden;
    text-overflow: ellipsis;
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
/* ---- showComponents ---- */
#showComponents{
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: rgba(0,0,0,0.2);
    z-index: 1;
    align-items: center;
    justify-content: center;
}
#components-holder{
    width: 50%;
    margin: auto;
    margin-top: 200px;
}
</style>
