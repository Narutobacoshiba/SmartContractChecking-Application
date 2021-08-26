<template>
    <div id="ud-body">
        <div id="upload-section">
            <div id="input-name">
                <div class="us-label">File name</div>
                <input type="text" v-model="fileupload_name" />
            </div>
            <div id="upload-file">
                <div class="us-label">Upload file (we accept the following file formats: .sol, .dcr, .lna):</div>
                <div id="ubtt-holder">
                    <input type="file" id="myfile" @change="uploadFile">
                </div>
            </div>
            <div id="upload-button" @click="saveUploadFile">
                Upload
            </div>
        </div>
        <div id="items-section">
            <div id="items-table">
                <div v-for="(item,idx) in items" :key="idx" class="itable-row">
                    <div class="iname-cell itable-cell">
                        {{item.name}}
                    </div>
                    <div class="iaction-cell itable-cell" @click="rmItems(idx)">
                        remove
                    </div>
                </div>
            </div>
            <div id="i-action">
                <div id="cancel-button" @click="CancelUl">
                    Cancel
                </div>
                <div id="update-button" @click="SaveUl">
                    Update
                </div>
            </div>
        </div>
    </div>
</template>

<script>
export default ({
    data(){
        return {
            fileupload_name: "",
            items: [],
        }
    },
    methods: {
        uploadFile(value){
            const file = value.target.files.item(0)
            this.fileupload_name = file.name
            /* const text = await file.text(); */
        },
        saveUploadFile(){
            if(this.fileupload_name != '')
            {
                let item = {id: this.hashValue(this.fileupload_name),name: this.fileupload_name, type: "upload"}
                this.items.push(item)
                this.fileupload_name = ''
            }
        },
        rmItems(idx){
            this.items.splice(idx,1)
        },
        CancelUl(){
            this.$emit("closeComponents")
        },
        SaveUl(){
            if(confirm("Are you sure to upadte your selection?")){
                this.CancelUl()
            }
        },
    }
})
</script>

<style scoped>
#ud-body{
    height: 412px;
    width: 600px;
    background-color: white;
    border-radius: 10px;
}

/* ---- upload-section ---- */
#upload-section{
    width: 90%;
    margin: 0 auto;
}

.us-label{
    font-size: 16;
    font-weight: bold;
    font-family: 'Lucida Sans';
}
#input-name{
    width: 100%;
}
#input-name input{
    width: 70%;
    height: 30px;
    border: none;
    border-radius: 4px;
    box-shadow: inset 0 1px 1px 0 #3d3d3d;
    font-size: 14px;
    color: rgb(51, 50, 50);
    padding-left: 5px;
}

#upload-file{
    width: 100%;
    margin-top: 10px;
}
#ubtt-holder{
    width: 70%;
    height: 30px;
    background-color: white;
    box-shadow: inset 0 1px 1px 0 #3d3d3d;
    border-radius: 4px;
    display: flex;
    align-items: center;
}

#ubtt-holder input{
    font-size: 12px;
    margin-left: 5px;
}

#upload-button{
    width: 80px;
    height: 25px;
    margin-top: 10px;
    background-color: green;
    color: white;
    padding-left: 14px;
    border-radius: 5px; 
    cursor: pointer;
}
#upload-button:hover{
    background-color: rgb(63, 104, 23);
}

/* ---- items-section ---- */
#items-section{
    width: 90%;
    margin: 0 auto;
    margin-top: 10px;
    border-top: 2px solid #6b6a6a;
}
#items-table{
    width: 100%;
    height: 192px;
    margin: 0 auto;
    margin-top: 10px;
    overflow-y: auto;
}
.itable-row{
    width: 96%;
    height: 30px;
    margin: 0 auto;
    margin-top: 2px;
    display: flex;
    align-items: center;
    border: 1px solid #6b6a6a;
    box-shadow: 1px 1px #888888;
}
.iname-cell{
    flex-basis: 80%;
    font-size: 13px;
    color: #444343;
    padding-left: 10px;
}
.iaction-cell{
    flex-basis: 20%;
    justify-content: center;
    color: white;
    background: rgb(212, 211, 211);
    cursor: pointer;
}
.iaction-cell:hover{
    background-color: rgb(194, 192, 192);
}
.itable-cell{
    display: flex;
    align-items: center;
    height: 30px;
}

#i-action{
    width: 100%;
    height: 40px;
    display: flex;
    justify-content: space-between;
    align-items: center;
}
#cancel-button{
    background-color: crimson;
    width: 80px;
    height: 25px;
    color: white;
    border-radius: 5px;
    display: flex;
    align-items: center;
    justify-content: center;
    cursor: pointer;
}
#cancel-button:hover{
    background-color: rgb(160, 14, 43);
}
#update-button{
    background-color: green;
    width: 80px;
    height: 25px;
    color: white;
    border-radius: 5px;
    display: flex;
    align-items: center;
    justify-content: center;
    cursor: pointer;
}
#update-button:hover{
    background-color: rgb(2, 87, 2);
}
</style>
