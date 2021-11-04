<template>
    <div id="iot-container">
        <div id="outc-set-limmit">
            <div class="outc-limmit-sec">
                <div>MinThreshold</div>
                <input type="text" v-model="min_threshold">
            </div>
            <div class="outc-limmit-sec">
                <div>MaxThreshold</div>
                <input type="text" v-model="max_threshold">
            </div>
        </div>

        <div id="outc-select-var">
            <VariableTable :selectValue="selected_var"/>
        </div>
    </div>
</template>

<script>
import VariableTable from "../smart-contract-table/VariableTable.vue"

export default({
    components: {VariableTable},
    data() {
        return{
            min_threshold: 0,
            max_threshold: 65535,
            selected_var: "",
        }
    },
})
</script>

<style scoped>
#iot-container{
    height: 100%;
    width: 100%;
}

#outc-set-limmit{
    display: flex;
    justify-content: space-between;
    padding-left: 10%;
    padding-right: 10%;
    height: 40px;
}

.outc-limmit-sec{
    display: flex;
    justify-content: space-between;
    align-items: center;
    height: 40px;
    font-weight: 500;
}

.outc-limmit-sec input{
    height: 26px;
    width: 100px;
    margin-left: 10px;
}

#outc-select-var{
    width: 100%;
    height: calc(100% - 50px);
    margin-top: 10px;
}
</style>
