var pg = require('pg');

var client = new pg.Client({
    user: 'test_user',
    host: '127.0.0.1',
    database: 'test',
    port: 5432
});

var data = [];
client.connect(err => {
    if (err) throw err;
    else {
        queryDatabase();
    }
});

function queryDatabase() {
    var query = `
        select * from illusts;
    `;

    client.query(query)
        .then(res => {
            const rows = res.rows;
            rows.map(row => {
                data.push(JSON.stringify(row));
                console.log(`Read: ${JSON.stringify(row)}`);
            });
            client.end(console.log('Closed client connection'));
        });
}

var header = document.querySelector('.header');
header.innerHTML = 'Pixiv Illusts';

var illust_list = document.querySelector('.illust_list');
var illusts = jsonObj['illusts'];
for (var i = 0; i != illusts.length; ++i) {
    var list_item = document.createElement('li');
    var illust_item = document.createElement('div');
    var title_item = document.createElement('div');
    var href = document.createElement('a');
    illust_item.setAttribute('class', 'illust');
    title_item.setAttribute('class', 'title');
    title_item.innerText = illusts[i]['title'];
    href.setAttribute('href', `/illust_page?illust_id=${illusts[i]['url']}`);
    var img = document.createElement('img');
    img.setAttribute('src', `/img?illusts=${illusts[i]['url']}`)
    img.setAttribute('class', 'img_small')
    
    href.appendChild(img);
    illust_item.appendChild(href);
    list_item.appendChild(illust_item);
    list_item.appendChild(title_item);
    illust_list.appendChild(list_item);
}
