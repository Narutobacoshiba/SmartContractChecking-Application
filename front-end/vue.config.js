module.exports = {
    devServer: {
        proxy: {
            "^/api": {
                target: 'http://192.168.1.28:8000/',
                ws: true,
                changeOrigin: true
            }
        }
    }
  }