<template>
  <div>
      <div v-if="ContextOfSmartContract">
        <context-of-smart-contract/>
      </div>
      <div v-if="LoadContext">
        <load-context/>
      </div>
      <div v-if="UpLoadContext">
        <up-load-context/>
      </div>
      <div v-if="UnFolding">
        <un-folding/>
      </div>
      <div v-if="ltlCheckingOption">
        <LTLCheckingOption/>
      </div>
  </div>
</template>

<script>
import ContextOfSmartContract from "../views/context/ContextOfSmartContract.vue"
import LoadContext from "../views/context/LoadContext.vue"
import UpLoadContext from "../views/context/UpLoadContext.vue"
import UnFolding from "../views/context/UnFolding.vue"
import LTLCheckingOption from "./choose-property/LTLCheckingOption.vue"
export default {
  components:{ContextOfSmartContract,LoadContext,UpLoadContext,UnFolding, LTLCheckingOption},
  data(){
    return {
      ContextOfSmartContract:false,
      LoadContext:false,
      UpLoadContext:false,
      UnFolding:true,
      ltlCheckingOption:false
    }
  }
}
</script>

<style>

</style>