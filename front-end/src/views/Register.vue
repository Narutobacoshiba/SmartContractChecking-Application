<template>
  <div class="form">
    <label>Full Name:</label>
    <input type="text" required v-model="fullname" placeholder="Full Name" />

    <label>Username:</label>
    <input type="text" required v-model="username" placeholder="User Name" />

    <label>Password:</label>
    <input type="password" required v-model="password" placeholder="Password" />
    <div v-if="error" class="error">{{ error }}</div>

    <div class="submit">
      <button @click="register()" id="register-btn">Register</button>
    </div>
    <div id="login-with">
      <button class="btn btn-google" type="submit">
        <i class="fab fa-google mr-2"></i> Continue with Google
      </button>
      <button class="btn btn-facebook" type="submit">
        <i class="fab fa-facebook-f mr-2"></i> Continue with Facebook
      </button>
    </div>
  </div>
</template>

<script>
export default {
  name: "login",
  data() {
    return {
      username: "",
      password: "",
      fullname: "",
      terms: false,
      error: "",
    };
  },
  methods: {
    register(){
    }
  },
};
</script>

<style scoped>
.form {
  max-width: 420px;
  margin: 30px auto;
  background: rgb(241, 240, 240);
  text-align: left;
  padding: 40px;
  border-radius: 10px;
}
label {
  color: rgb(97, 94, 94);
  display: inline-block;
  margin: 25px 0 15px;
  font-size: 0.6em;
  text-transform: uppercase;
  letter-spacing: 1px;
  font-weight: bold;
}
input {
  display: block;
  padding: 10px 6px;
  width: 100%;
  box-sizing: border-box;
  border-style: solid;
  border-color: rgb(163, 161, 161);
  border-radius: 10px;
  color: rgb(126, 126, 126);
}
input[type="checkbox"] {
  display: inline-block;
  width: 16px;
  margin: 0 10px 0 0;
  position: relative;
  top: 2px;
}
button {
  width: 100%;
  background: #0b6dff;
  border: 0;
  padding: 10px 20px;
  margin-top: 20px;
  color: white;
  border-radius: 20px;
}
.submit {
  text-align: center;
}
#register-btn{
    width: 50%;
}
.error {
  color: #ff0062;
  margin-top: 10px;
  font-size: 0.8em;
  font-weight: bold;
}
#login-with {
  width: 100%;
  margin-top: 20px;
  padding-top: 20px;
  border-top-style: solid;
  border-top-color: #777;
  border-top-width: 1px;
}
.btn-google {
  color: white;
  background-color: #ea4335;
}
.btn-facebook {
  color: white;
  background-color: #3b5998;
}
.btn {
  font-size: 80%;
  border-radius: 5rem;
  letter-spacing: 0.1rem;
  font-weight: bold;
  padding: 1rem;
  transition: all 0.2s;
  width: 100%;
}
</style>