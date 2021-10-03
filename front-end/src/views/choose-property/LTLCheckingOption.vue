<template>
  <div>
    <h1> (15) LTL Checking Option</h1>
    <div v-if="CheckCSP">
      <contract-specific-property />
    </div>
    <div v-if="CheckGV">
      <genaral-vul-setting/>
    </div>
  </div>
</template>

<script>
import ContractSpecificProperty from "./CheckContractSpecificProperty/ContractSpecificProperty.vue";
import GenaralVulSetting from "./CheckGeneralVul/GenaralVulSetting.vue"
export default {
  data(){
    return{
      CheckCSP:false,
      CheckGV:true
    }
  },
  components: { ContractSpecificProperty,GenaralVulSetting },
};
</script>

<style>
</style>