<template>
  <div>
      <h1>Select Smart Contract</h1>
      <button @click="Add()">Add</button>
      <button @click="upLoadfile()">Upload File</button>
      <button @click="backToList()">Back</button>
      <button>Next</button>
  </div>
</template>

<script>
export default {
    methods:{
        upLoadfile(){}, // Up load file SmartContract
        backToList(){}, //Back to ListOfCheckedTransactions (open Upload New SmartContract Code)
        Add(){},//Add SmartContract and go to 
    }
}
</script>

<style>

</style>