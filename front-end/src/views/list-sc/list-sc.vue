<template>
    <div id="body">
        <div id="first-section"></div>
        <div id="second-section"></div>
        <div id="third-section">
            <div id="select-section">
                <div class="select-box" :class="{chosen_box: chosen_table == 'common'}" @click="ChooseTable('common')">
                    <p>Common Smart Contracts</p>
                </div>
                <div class="select-box" :class="{chosen_box: chosen_table == 'private'}" @click="ChooseTable('private')">
                    <p>Priviate Smart Contracts</p>
                </div>
                <div class="select-box" :class="{chosen_box: chosen_table == 'pending'}" @click="ChooseTable('pending')" v-if="isSuperior">
                    <p>Pending Smart Contracts</p>
                </div>
            </div>
            <div id="table-section">
                <div id="table-name">
                    <div id="add-button" @click="addSmartContract" v-if="showAddButton">
                        Add
                    </div>
                    <p>{{GetTableName}}</p>
                </div>
                <div id="table-body">
                    <div id="table-header" class="table-row">
                        <div class="index-cell table-cell">
                            #
                        </div>
                        <div class="name-cell table-cell">
                            Smart contracts name
                        </div>
                        <div class="date-modified-cell table-cell">
                            Date modified
                        </div>
                        <div class="action-cell table-cell">
                            Action
                        </div>
                    </div>
                    <div id="table-content">
                        <div v-for="(sc,idx) in list_smart_contracts[chosen_table]" :key="idx" class="table-row">
                            <div class="index-cell table-cell">
                                {{inc(idx)}}
                            </div>
                            <div class="name-cell table-cell">
                                {{sc.name}}
                            </div>
                            <div class="date-modified-cell table-cell">
                                {{convertDate(sc.date_modified)}}
                            </div>
                            <div class="action-cell table-cell">
                                <div v-if="chosen_table != 'pending'">
                                    <i class="material-icons" @click="editSC(sc.id,sc.name)">edit</i>
                                    <i class="material-icons" @click="deleteSC(sc.id,sc.name,chosen_table)">delete</i>
                                </div>
                                <div v-else>
                                    <i class="material-icons" @click="editSC(sc.id,sc.name)">edit</i>
                                    <i class="material-icons" @click="acceptPendingSC(sc.id,sc.name)">check_circle_outline</i>
                                    <i class="material-icons" @click="deleteSC(sc.id,sc.name,chosen_table)">delete</i>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import {GetCommonSmartContracts, GetPendingSmartContracts, 
       GetPrivateSmartContracts, DeleteSmartContracts, 
       AddNewSmartContractsInfor} 
from "../../services/data"

export default ({
    data(){
        return {
            chosen_table: "common",
            list_smart_contracts: {
                common: [],
                private: [],
                pending: []
            }
        }
    },
    mounted(){
        this.list_smart_contracts.common = GetCommonSmartContracts()
        this.list_smart_contracts.private = GetPrivateSmartContracts()
        this.list_smart_contracts.pending = GetPendingSmartContracts()

    },
    computed: {
        GetTableName(){
            if(this.chosen_table == "common"){
                return "Common Smart Contracts"
            }
            if(this.chosen_table == "private"){
                return "Private Smart Contracts"
            }
            if(this.chosen_table == "pending"){
                return "Pending Smart Contracts"
            }
            return "Invalid Table"
        },
        showAddButton(){
            return (this.chosen_table != 'pending') && 
                  (this.chosen_table != 'common' || (this.$store.state.user.currentUser.role == 'admin'))
        },
        isSuperior(){
            return this.$store.state.user.currentUser.role == 'admin'
        }
    },
    methods: {
        inc(value){
            return value+1
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
        ChooseTable(value){
            this.chosen_table = value
        },
        addSmartContract(){
            this.$router.push({name: "AddSc",params: {options: this.chosen_table, parent_path: "/list-sc"}})
        },
        deleteSC(sc_id, sc_name, option){
            if(confirm("Are you sure to delete the Smart Contract named: '"+sc_name+"' ?")){
                DeleteSmartContracts(sc_id, option)
            }
        },
        editSC(sc_id, sc_name){
            this.$router.push({name: "EditSc", params: {sc_id: sc_id, name: sc_name, parent_path: "/list-sc"}})
        },
        acceptPendingSC(sc_id, sc_name){
            AddNewSmartContractsInfor(sc_id,sc_name,"common")
            DeleteSmartContracts(sc_id,"pending")
        }
    }
})
</script>

<style scoped>
#body{
    width: 100%;
    min-width: 750px;
}
#first-section{
    height: 100px;
    width: 100%;
    background-color: #fafafa;
    border-bottom: 1px solid #d8d7d7;
    border-top: 1px solid #d8d7d7;
}
#second-section{
    height: 600px;
    width: 100%;
    background-color: #ffffff;
}
#third-section{
    height: 600px;
    width: 86%;
    margin: 0 auto;
    margin-top: -700px;

    background-color: transparent;
}

#select-section{
    width: 100%;
    height: 70px;
}

.select-box{
    width: 200px;
    height: 40px;
  
    display: inline-block;
    margin-top: 15px;
    margin-bottom: 15px;
    margin-right: 10px;

    border: 0.5px solid #d8d7d7;
    border-radius: 4px;
    
    font-size: 15px;
    text-align: center;
    vertical-align: middle;

    cursor: pointer;
}
.select-box p{
    margin-top: 8px;
    color: #1967d2;
}
.select-box:hover{
    background-color: #e9eef7;
}

#table-section{
    width: 100%;
    height: 600px;

    background-color: white;
    border: 1px solid #d8d7d7;
    border-radius: 8px;
    box-shadow: 0 1px 4px 0 rgba(0,0,0,0.37);
}
#table-name {
    width: 100%;
    height: 80px;

    border-bottom: 1px solid #d8d7d7;
    text-align: center;

    color: #6b6e73;
    padding: 12px;
}
#table-name p {
    font-size: 32px;
}
#table-name #add-button{
    position: absolute;
    margin-top: 15px;
    margin-left: 2%;

    height: 30px;
    width: 60px;
    border: 1px solid #5c5b5b;
    box-shadow: 2px 2px 0px 0px rgb(78, 77, 77);
    padding: 2px;
    cursor: pointer;
}
#table-name #add-button:hover{
    background-color: #d8d7d7;
    color: #272626;
}
#table-body{
    width: 100%;
    height: 520px;
    overflow-y: auto;
}
#table-header{
    background-color: #c9dff0;
    color: #4d4c4c;
    font-size: 16px;
    font-weight: bold;
}

/* --- table row --- */
.table-row{
    width: 100%;
    height: 60px;
    
    display: flex;
    align-items: center;
    color: #585858;

    border-bottom: 0.5px solid #d8d7d7;
}
.index-cell{
    height: 24px;
    flex-basis: 10%;
    text-align: center;
}
.name-cell{
    height: 24px;
    flex-basis: 40%;
}
.date-modified-cell{
    height: 24px;
    flex-basis: 30%;
}
.action-cell{
    height: 40px;
    flex-basis: 20%;
    text-align: center;
}
.action-cell i{
    padding: 8px;
    color: #858383;
    cursor: pointer;
}
.table-cell{
    overflow: hidden;
    text-overflow: ellipsis;
}
.table-row:hover{
    background-color: #fafafa;
}
.action-cell i:hover{
    color: #5e5d5d;
}

/* --- box --- */
.chosen_box{
    background-color: #e4ecfa;
}
</style>