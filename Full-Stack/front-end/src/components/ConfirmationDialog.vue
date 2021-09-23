<template>
    <div id="dialog" class="container">
        <div id="d-header">{{this.dialog.title}}<hr></div>
        <div id="d-content">{{this.dialog.message}}</div>
        <div id="btn-group" class="container">
            <button class="btn btn-secondary btn-sm" @click="cancel">Cancel</button>
            <button class="btn btn-success btn-sm" @click="confirm">{{this.dialog.confirmbtn}}</button>
        </div>
    </div>
</template>
<script>
export default {
    props: ["dialog"],
    methods:{
        cancel(){
            this.$emit("cancel")
        },
        confirm(){
            this.$emit("confirm")
        }
    }
}
</script>
<style scoped>
#dialog{
    width: 450px;
    height: 180px;
    /* border: 1px solid gray; */
    margin: auto;
    background-color: white;
    border-radius: 5px;
    padding: 15px;
}
#d-header{
    font-size: 23px;
    height: 60px;
    color: #3a7694;
}
hr{
    margin-top: 10px;
}
#d-content{
    height: 60px;
}
#btn-group{
    width: 50%;
    float: right;
    display: flex;
    justify-content: space-evenly;
    margin: auto;
}
</style>
