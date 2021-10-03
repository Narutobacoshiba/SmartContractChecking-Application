<template>
  <div>
      <h1>SelectSc</h1>
      <div v-if="isListChecked">
        <ListOfCheckedTransactions/>
      </div>
      <div v-if="CheckReenTrancyDetail">
        <CheckReenTrancyDetail />
      </div>
      <div v-if="showSelectSmartContract">
        <SelectSmartContract/>
      </div>
      <div v-if="UploadANewSmartContractCode">
        <UpLoadSc/>
      </div>
  </div>
</template>

<script>
import ListOfCheckedTransactions from "./select-sc/transactions/ListOfCheckedTransactions.vue"
import CheckReenTrancyDetail from "./select-sc/transactions/CheckReenTrancyDetail.vue"
import SelectSmartContract from "../views/select-sc/smartcontract/SelectSmartContract.vue"
import UpLoadSc from "../views/select-sc/smartcontract/UpLoadSc.vue"
export default {
  components:{ListOfCheckedTransactions,CheckReenTrancyDetail,SelectSmartContract,UpLoadSc},
  data(){
    return{
      isListChecked:true,
      CheckReenTrancyDetail:false,
      showSelectSmartContract:false,
      UploadANewSmartContractCode:false
    }
  },
}
</script>

<style>

</style>