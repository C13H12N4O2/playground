var querystring = require("querystring"),
    fs = require("fs"),
    formidable = require("formidable"),
    exec = require("child_process").exec,
    url = require("url"),
    Client = require("./client");

var test_i = 2;

function start(response) {
    console.log("Request handler 'start' was called.");
    
    var body = '<html>'+
        '<head>'+
        '<meta http-equiv="Content-Type" '+
        'content="text/html; charset=UTF-8" />'+
        '</head>'+
        '<body>'+
        '<form action="/upload" enctype="multipart/form-data" '+
        'method="post">'+
        '<input type="file" name="upload">'+
        '<input type="submit" value="Upload file" />'+
        '</form>'+
        '</body>'+
        '</html>';
    
    response.writeHead(200, {"Content-Type": "text/html"});
    response.write(body);
    response.end();
}

function upload(response, request) {
    console.log("Request handler 'upload' was called.");
    
    var form = new formidable.IncomingForm();
    
    console.log("about to parse");
    form.parse(request, function(error, fields, files) {
        console.log("parsing done");
        fs.renameSync(files.upload.path, `./tmp/${files["upload"]["name"]}`);
        var query = `
            create table if not exists illusts (illust_id serial PRIMARY KEY, name varchar(50));
            insert into illusts (illust_id, name) values (${test_i}, '${files["upload"]["name"]}');
        `;
        ++test_i;
        
        Client.test(query);
        
        response.writeHead(200, {"Content-Type": "text/plain"});
        response.write("received image:<br/>");
        response.write("<img src='/show' />");
        response.end();
    });
}

function show(response) {
    console.log("Request handler 'show' was called.");
    
    fs.readFile('public/show.html', function(error, content) {
        response.writeHead(200, { 'Content-Type': "text/html" });
        response.end(content, 'utf-8');
    })
}

function illust_page(response, request) {
    console.log("Request handler 'illust_page' was called.");
    
    fs.readFile('public/illust_page.html', function(error, content) {
        response.writeHead(200, { 'Content-Type': "text/html" });
        response.end(content, 'utf-8');
    });
}

function img(response, request) {
    console.log("Request handler 'img' was called.");
    
    var bs = url.parse(request.url);
    var query = querystring.parse(bs.query);
    
    response.writeHead(200, {"Content-Type": "image/jpg"});
    fs.createReadStream(`tmp/${query['illusts']}`).pipe(response);
}

function test(response, request) {
    console.log("Request handler 'test' was called.");
    
    document.open();
}

function public(response, request) {
    console.log("Request handler 'public' was called.");
    
    var bs = url.parse(request.url);
    var query = querystring.parse(bs.query);
    
    fs.readFile(`public/${query['name']}`, function(error, content) {
        response.writeHead(200, { 'Content-Type': "text/css" });
        response.end(content, 'utf-8');
    });
}

function json(response, request) {
    console.log("Request handler 'json' was called.");
    
    var bs = url.parse(request.url);
    var query = querystring.parse(bs.query);
    
    fs.readFile(`public/${query['name']}`, function(error, content) {
        response.writeHead(200, { 'Content-Type': "text/json" });
        response.end(content, 'utf-8');
    });
}

exports.start = start;
exports.upload = upload;
exports.show = show;
exports.illust_page = illust_page;
exports.img = img;
exports.test = test;
exports.public = public;
exports.json = json;
