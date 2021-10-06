<template>
  <transition name="flip" mode="out-in">
    <router-view></router-view>
  </transition>
</template>

<script>
export default {
  components: {},
  data() {
    return {
      isListChecked: false,
      CheckReenTrancyDetail: false,
      showSelectSmartContract: false,
      UploadANewSmartContractCode: false,
    };
  },
};
</script>

<style>
.flip-enter-active,
.flip-leave-active {
  transition: transform 0.3s ease-out;
}
.flip-enter {
  transform: rotateY(90deg);
}
.flip-leave-to {
  transform: rotateY(90deg);
}
</style>