<template>
    <div id="ud-body">
        <div id="title">Upload your files</div>
        <div id="upload-section">
            
            <div id="upload-file">
                <div class="us-label">Accepted file types: <span>.sol</span>, <span>.dcr</span>, <span>.lna</span></div>
                
                <div>
                    <input type="file" id="myfile" @change="uploadFile">
                </div>
            </div>
            <div id="input-name">
                <div class="us-label">File name</div>
                <input class="form-control form-control-sm" type="text" v-model="fileupload_name" />
            </div>
            <div id="upload">
                <button class="btn btn-primary btn-sm" id="upload-button" @click="saveUploadFile">
                    Upload
                </button>
            </div>
        </div>
        
        <div id="items-section">
            <hr class="my-4">
            <div id="items-table">
                <div v-for="(item,idx) in items" :key="idx" class="itable-row">
                    <div class="iname-cell itable-cell">
                        {{item.name}}
                    </div>
                    <div class="" >
                        <button class="iaction-cell itable-cell" @click="rmItems(idx)">Remove</button>
                    </div>
                </div>
            </div>
            <div id="i-action">
                <div id="cancel-button" @click="CancelUl">
                    Cancel
                </div>
                <div id="update-button" @click="SaveUl">
                    Save
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
            if(confirm("Are you sure to update your selection?")){
                this.CancelUl()
            }
        },
    }
})
</script>

<style scoped>
#ud-body{
    height: 510px;
    width: 600px;
    background-color: white;
    padding: 0 0 20px 0;
    border-radius: 5px;
}

/* ---- upload-section ---- */
#upload-section{
    width: 90%;
    margin: 0 auto;
}
#title{
    font-weight: bold;
    text-align: center;
    font-size: 20px;
    background-color: #d9edf7;
    color: #3a7694;
    padding-top: 20px;
    padding-bottom: 10px;
    border-top-left-radius: 5px;
    border-top-right-radius: 5px;
}
.us-label{
    font-size: 16;
    font-family: 'Lucida Sans';
    color: #373A3C;
}
#input-name{
    width: 100%;
    margin-bottom: 10px;
}
#input-name input{
    width: 100%;
}

#upload-file{
    width: 100%;
    margin-top: 10px;
    margin-bottom: 10px;
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

#upload{
    text-align: center;
    margin-top: 15px;
}
#upload-button{
    width: 80px;
    height: auto;
    border-radius: 2px;
    margin-bottom: 0;
}
/* ---- items-section ---- */
#items-section{
    width: 90%;
    margin: auto;
}
#items-table{
    width: 100%;
    height: 162px;
    margin: 0 auto;
    overflow-y: auto;
}
.itable-row{
    width: 96%;
    height: 30px;
    margin: 0 auto;
    margin-bottom: 2px;
    display: flex;
    align-items: center;
    box-shadow: 1px 1px #d4d3d3;
}
.itable-row:hover{
    background-color: #EFEFEF;
}
.iname-cell{
    flex-basis: 90%;
    font-size: 14px;
    color: #444343;
    padding-left: 10px;
}
.iaction-cell{
    flex-basis: 10%;
    justify-content: center;
    color: #212529;
    background: rgb(212, 211, 211);
    cursor: pointer;
}
.btn{
    width: 100%;
    margin: 0;
}
.iaction-cell:hover{
    background-color: rgb(194, 192, 192);
}
.itable-cell{
    display: flex;
    align-items: center;
    height: 30px;
    border: none;
}

#i-action{
    margin-top: 15px;
    margin-bottom: 15px;
    width: 100%;
    height: 40px;
    display: flex;
    justify-content: space-between;
    align-items: center;
}
#cancel-button{
    
    width: 80px;
    height: 25px;
    border-radius: 2px;
    display: flex;
    align-items: center;
    justify-content: center;
    cursor: pointer;
    background-color: #fd647a;
    color: white;
}
#cancel-button:hover{
    background-color: #dc3545;
    color: white;
}
#update-button{
    background-color: green;
    width: 80px;
    height: 25px;
    color: white;
    border-radius: 2px;
    display: flex;
    align-items: center;
    justify-content: center;
    cursor: pointer;
}
#update-button:hover{
    background-color: rgb(2, 87, 2);
}
span{
    color: red;
    font-weight: bold;
}
</style>
