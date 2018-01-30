package client;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.util.Bytes;
import util.HBaseHelper;

public class PutExample {

    @SuppressWarnings("deprecation")
    public static void main(String[] args) throws IOException {
        Configuration conf = HBaseConfiguration.create();

        HBaseHelper helper = HBaseHelper.getHelper(conf);
        helper.dropTable("testtable");
        helper.createTable("testtable", "colfam1");

        HTable table = new HTable(conf, "testtable");

        Put put = new Put(Bytes.toBytes("row1"));
        put.add(Bytes.toBytes("colfam1"), Bytes.toBytes("qual1"),
            Bytes.toBytes("val1"));
        put.add(Bytes.toBytes("colfam1"), Bytes.toBytes("qual2"),
            Bytes.toBytes("val2"));

        table.put(put);
    }
}
