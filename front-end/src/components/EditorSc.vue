<template>
  <div id="editor">
    <div class="text-edit textarea">
      <!-- <textarea
        id="code"
        name="code"
        :value="code"
        v-on:input="$emit('input', $event.target.value)"
      >
      </textarea> -->
      <AceEditor />
    </div>
  </div>
</template>

<script>
import AceEditor from "./AceEditor.vue";
export default {
  name: "editor",
  model: {
    prop: "code",
    event: "input",
  },
  props: {
    code: String,
  },
  data() {
    return {};
  },
  components: { AceEditor },
  methods: {},
};
</script>

<style scoped>
#code {
  width: 400px;
  height: 300px;
  border: 1px solid;
}
#editor {
  width: 100%;
  font-style: normal;
}
.tool-edit {
  background-color: darkgray;
  width: 50%;
  display: flex;
  justify-content: space-between;
  overflow: hidden;
  border: 1px solid;
}
.ic:hover {
  opacity: 0.8;
  cursor: pointer;
}
.textarea {
  overflow: hidden;
}
</style>
