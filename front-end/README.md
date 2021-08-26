# Front End

## Project setup
```
npm install
```

### Compiles and hot-reloads for development
```
npm run serve
```

### Test backend
### `backend`
warning: tải file vue.config.js về để tránh lỗi CORS (Cross-origin resource sharing) khi api gọi đến domain khác vs domain đang chạy

Chạy backend để xem sự khác nhau giữa hiển thị của user thường và admin

User account:

```
username: hadt  pass: 012345
```

Admin account:

```
username: bantq  pass: 123456
```

-Để bỏ qua tính năng authentication vs authorization nhằm phát triển view dễ hơn thì trong file ./src/router/index.js thay đổi theo sau:

```
import Vue from "vue";
import VueRouter from "vue-router";

/* import { initCurrentUserStateMiddleware, checkAccessMiddleware, setPageTitleMiddleware } from './middlewares' */
import { routes } from './routes'

Vue.use(VueRouter);

const router = new VueRouter({
  mode: "history",
  base: process.env.BASE_URL,
  routes,
});

/* router.beforeEach(initCurrentUserStateMiddleware)
router.beforeEach(checkAccessMiddleware)
router.beforeEach(setPageTitleMiddleware) */

export default router;
```

```
get help
```


### Cấu trúc project

### `src`
folder nguồn

### `assets`
Images/Fonts/Other

### `components`
chứa các component

### `router`
Router instance và routing declaration.
- `index` - router initialization.
- `routes` - routing.
- `middlewares`:
  - `initCurrentUserStateMiddleware` - ......
  - `checkAccessMiddleware` - mỗi khi người dùng thay đổi hướng check quyền chuyển hướng
  - `setPageTitleMiddleware` - mỗi khi người dùng thay đổi hướng thay đổi title của trang cho phù hợp

### `services`
Data access layer / API calls.
sử dụng jwt authorization thay cho seesion cookies.

### `store`
App store với một vài modules.

### `views`
Các màn hình chính của project

### `.env.js`
Biến môi trường
