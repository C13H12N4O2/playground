var pg = require('pg');

function test() {
    var client = new pg.Client({
        user: 'test_user',
        host: '127.0.0.1',
        database: 'test',
        port: 5432
    });
    
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
                    console.log(`Read: ${JSON.stringify(row)}`);
                });
                client.end(console.log('Closed client connection'));
            });
    }
}

exports.test = test;
