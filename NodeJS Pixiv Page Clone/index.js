var server = require("./server");
var router = require("./router");
var requestHandlers = require("./requestHandlers");

var handle = {}
handle["/"] = requestHandlers.start;
handle["/start"] = requestHandlers.start;
handle["/upload"] = requestHandlers.upload;
handle["/show"] = requestHandlers.show;
handle["/illust_page"] = requestHandlers.illust_page;
handle["/img"] = requestHandlers.img;
handle["/test"] = requestHandlers.test;
handle["/public"] = requestHandlers.public;
handle["/json"] = requestHandlers.json;

server.start(router.route, handle);

