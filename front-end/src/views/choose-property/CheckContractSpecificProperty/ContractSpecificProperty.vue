<template>
  <div>
    <h1>(16)Contract-Specifc Property Setting - Choose Types</h1>
    <div>
      <CSPTemplateSetting />
    </div>
    <div>
      <div>
      <ContractSpecificPropertyNonTemplate/>
      </div>
    </div>
  </div>
</template>

<script>
import CSPTemplateSetting from "./CSPTemplate/CSPTemplateSetting.vue";
import ContractSpecificPropertyNonTemplate from "./ContractSpecificPropertyNonTemplate.vue"
export default {
  components: { CSPTemplateSetting,ContractSpecificPropertyNonTemplate },
};
</script>

<style>
</style>