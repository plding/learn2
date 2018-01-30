package client;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.KeyValue;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.util.Bytes;
import util.HBaseHelper;

public class GetRowOrBeforeExample {

    @SuppressWarnings("deprecation")
    public static void main(String[] args) throws IOException {
        Configuration conf = HBaseConfiguration.create();

        HBaseHelper helper = HBaseHelper.getHelper(conf);
        if (!helper.existsTable("testtable")) {
            helper.createTable("testtable", "colfam1");
        }

        HTable table = new HTable(conf, "testtable");

        Result result1 = table.getRowOrBefore(Bytes.toBytes("row1"),
            Bytes.toBytes("colfam1"));
        System.out.println("Found: " + Bytes.toString(result1.getRow()));

        Result result2 = table.getRowOrBefore(Bytes.toBytes("row99"),
            Bytes.toBytes("colfam1"));
        System.out.println("Found: " + Bytes.toString(result2.getRow()));

        for (KeyValue kv : result2.raw()) {
            System.out.println(" Col: " + Bytes.toString(kv.getFamily()) +
                "/" + Bytes.toString(kv.getQualifier()) +
                ", Value: " + Bytes.toString(kv.getValue()));
        }

        Result result3 = table.getRowOrBefore(Bytes.toBytes("abc"),
            Bytes.toBytes("colfam1"));
        System.out.println("Found: " + result3);
    }
}
