<template>
    <div id="table-list">
        <div class="table-row" id="header-row">
            <div class="table-cell header-cell first-cell">
                #
                <span class="material-icons"> swap_vert </span>
            </div>
            <div class="table-cell header-cell second-cell">
                Contract Name
                <span class="material-icons"> swap_vert </span>
            </div>
        </div>

        <div id="table-content">
            <div class="table-row" v-for="(val, index) in getListSc" v-bind:key="val.id" :class="{ even_row: index % 2 == 0}">
                <div class="table-cell first-cell">{{ index+1 }}</div>
                <div class="table-cell second-cell">{{ val.name }}</div>
            </div>
        </div>
    </div>
</template>


<script>
export default ({
    data(){
        return{
            list_smart_contract: [],
        }
    },
    mounted(){
        this.list_smart_contract = this.$store.getters["data/GetSelectedSC"]
    },
    computed:{
        getListSc(){
            return this.list_smart_contract
        }
    }
})
</script>

<style scoped>
#table-list {
  width: 100%;
  margin: auto;
  font-size: 0.9em;
  height: 100%;
  border-radius: 4px;
  border: 2px solid black;
  
  background: rgb(241, 240, 240);
}
#table-content{
    height: 80%;
    overflow-y: auto;
}
.table-row{
  display: flex;
  height: 20%;
}
#header-row{
  background-color: rgb(196, 194, 194);
  font-weight: bold;
  height: 20%;
}
#table-list span {
  float: right;
  margin: 0 20% 0 0;
  padding: 0;
  font-size: 150%;
}
.even_row{
  background-color: rgb(226, 224, 224);
}
.table-cell{
  display: flex;
  align-items: center;
}
.first-cell{
  flex-basis: 30%;
  padding-left: 5px;
  display: flex;
  justify-content: space-between;
}
.second-cell{
  flex-basis: 70%;
  display: flex;
  justify-content: space-between;
}
</style>