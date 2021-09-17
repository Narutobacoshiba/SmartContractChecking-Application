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
                    <p>Private Smart Contracts</p>
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
                        <div v-for="sc in smartcontracts" :key="sc.id" class="table-row">
                            <div class="index-cell table-cell">
                                {{sc.id}}
                            </div>
                            <div class="name-cell table-cell">
                                {{sc.name}}
                            </div>
                            <div class="date-modified-cell table-cell">
                                
                            </div>
                            <div class="action-cell table-cell">
                                <div >
                                    <i class="material-icons" @click="editSC(sc.id,sc.name)">edit</i>
                                    <i class="material-icons" @click="deleteSmartContracts(sc)">delete</i>
                                </div>
                               
                            </div>
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
                <i class="material-icons" id="itb-next-page-icon" @click="goPage(pageNum < numOfPage ? (pageNum+1):numOfPage)">chevron_right</i>
                <i class="material-icons" id="itb-last-page-icon" @click="goPage(numOfPage)">last_page</i>
            </div>
        </div>
        </div>
    </div>
</template>
<script>

export default {
  name: 'App',
  data(){
    return{
      chosen_table: "common",
      smartcontract: {
      },
      smartcontracts: []
    }
  },
  async created(){
    await this.getSmartContracts();
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
  },
  methods: {
    async getSmartContracts(){
      var response = await fetch('http://localhost:8000/api/smartcontracts/');
      this.smartcontracts = await response.json();
    },
    async deleteSmartContracts(sc){
      await this.getSmartContracts();
       if(confirm("Are you sure to delete the Smart Contract named: '"+sc.name+"' ?")){
                await fetch(`http://localhost:8000/api/smartcontracts/${sc.id}/`, {
          method: 'delete',
          headers: {
              'Content-Type': 'application/json'
          },
          body: JSON.stringify(this.sc)
      });
            }
      
        await this.getSmartContracts();
    }
  }
}
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
    height: 560px;

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
</style>