# Front End

## Project setup
```
npm install
```

### Compiles and hot-reloads for development
```
npm run serve
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
