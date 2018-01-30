package client;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Get;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.util.Bytes;
import util.HBaseHelper;

public class GetExample {

    @SuppressWarnings("deprecation")
    public static void main(String[] args) throws IOException {
        Configuration conf = HBaseConfiguration.create();

        HBaseHelper helper = HBaseHelper.getHelper(conf);
        if (!helper.existsTable("testtable")) {
            helper.createTable("testtable", "colfam1");
        }

        HTable table = new HTable(conf, "testtable");

        Get get = new Get(Bytes.toBytes("row1"));
        get.addColumn(Bytes.toBytes("colfam1"), Bytes.toBytes("qual1"));

        Result result = table.get(get);
        byte[] val = result.getValue(Bytes.toBytes("colfam1"), Bytes.toBytes("qual1"));

        System.out.println("Value: " + Bytes.toString(val));
    }
}
