package client;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.Get;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.util.Bytes;
import util.HBaseHelper;

import java.io.IOException;

public class PutWriteBufferExample {

    public static void main(String[] args) throws IOException {
        Configuration conf = HBaseConfiguration.create();

        HBaseHelper helper = HBaseHelper.getHelper(conf);
        helper.dropTable("testtable");
        helper.createTable("testtable", "colfam1");

        HTable table = new HTable(conf, "testtable");
        System.out.println("Auto flush: " + table.isAutoFlush());

        table.setAutoFlush(false);

        Put put1 = new Put(Bytes.toBytes("row1"));
        put1.add(Bytes.toBytes("colfam1"), Bytes.toBytes("qual1"),
            Bytes.toBytes("val1"));
        table.put(put1);

        Put put2 = new Put(Bytes.toBytes("row2"));
        put2.add(Bytes.toBytes("colfam1"), Bytes.toBytes("qual1"),
            Bytes.toBytes("val2"));
        table.put(put2);

        Put put3 = new Put(Bytes.toBytes("row3"));
        put3.add(Bytes.toBytes("colfam1"), Bytes.toBytes("qual1"),
            Bytes.toBytes("val3"));
        table.put(put3);

        Get get = new Get(Bytes.toBytes("row1"));
        Result res1 = table.get(get);
        System.out.println("Result: " + res1);

        table.flushCommits();

        Result res2 = table.get(get);
        System.out.println("Result: " + res2);
    }
}
