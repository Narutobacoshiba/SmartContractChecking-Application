<template>
    <div id="main">
        <div id="header">Manage LTL Vulnerabilities</div>
        <div id="add" class="container"><button class="btn btn-outline-primary btn-sm" @click="goAdd">Add an LTL Vulnerability</button></div>
        <div id="table" class="container">
            <div id="tbl-header" class="row">
                <div class="col-2 title">ID</div>
                <div class="col-8 title">Name</div>
                <div class="col-2 title">Action</div>
            </div>
            <div v-for="vul in list_vuls" :key="vul.id" class="row list">
                <div class="col-2">{{vul.id}}</div>
                <div class="col-8">{{vul.name}}</div>
                <div class="col-2">
                    <i class="material-icons" @click="editVul(vul.id)">edit</i>
                    <i class="material-icons" @click="deleteVul(vul.id)">delete</i>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import {GetLtl, DeleteLtl} from "../../services/data"

export default {
    data(){
        return {
            list_vuls: []
        }
    },
    mounted(){
      this.initData()
    },
    methods:{
        async initData(){
             this.list_vuls = await GetLtl() 
        },
        goAdd(){
            this.$router.push({name: "AddVul" ,params: {parent_path: "/list-vul"}})
        },
        editVul(id){
            this.$router.push({name: "EditVul" ,params: {vul_id: id, parent_path: "/list-vul"}})
        },
        async deleteVul(id){
             if(!confirm(`Do you want to delete LTL `)){
        return
      }
      const response = await DeleteLtl(id);
      if(response.status === 200){
          await this.initData()
      }
            for (var i=0; i<this.list_vuls.length; i++) {
                if (this.list_vuls[i].id == id) {
                    this.list_vuls.splice(i, 1);
                    break
                }
            }
        },
    },
    created(){
        //this.list_vuls = {function to get vulnerabilities from DB}
    }
}
</script>

<style scoped>
#main{
    padding-top: 20px;
    background-color: #fafafa;
    height: auto;
    min-height: 100vh;
}
#header{
    margin: auto;
    text-align: center;
    font-size: 35px;
    margin-bottom: 20px;
}
#add{
    width: 70%;
    padding: 0;
    margin-bottom: 10px;
}
#table{
    width: 70%;
    min-width: 600px;
    margin: auto;
    height: 450px;
    border: 1px solid lightblue;
    border-radius: 3px;
}
#tbl-header{
    background-color: #d9edf7;
    height: 40px;
    align-items: center;
    font-weight: bold;
}
#table .list{
    height: 35px;
    border-bottom: 0.5px solid #d8d7d7;
    vertical-align: middle;
    align-items: center;
}
#table .list:hover{
    background-color: #ebebeb;
}
i{
    cursor: pointer;
    margin-right: 10px;
}
</style>