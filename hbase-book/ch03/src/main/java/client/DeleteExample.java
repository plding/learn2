package client;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.Delete;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.util.Bytes;
import util.HBaseHelper;

public class DeleteExample {

    @SuppressWarnings("deprecation")
    public static void main(String[] args) throws IOException {
        Configuration conf = HBaseConfiguration.create();

        HBaseHelper helper = HBaseHelper.getHelper(conf);
        helper.dropTable("testtable");
        helper.createTable("testtable", "colfam1", "colfam2");

        helper.put("testtable",
            new String[] { "row1" },
            new String[] { "colfam1", "colfam2" },
            new String[] { "qual1", "qual1", "qual2", "qual2", "qual3", "qual3" },
            new long[]   { 1, 2, 3, 4, 5, 6 },
            new String[] { "val1", "val2", "val3", "val4", "val5", "val6" });
        System.out.println("Before delete call...");
        helper.dump("testtable", new String[] { "row1" }, null, null);

        HTable table = new HTable(conf, "testtable");

        Delete delete = new Delete(Bytes.toBytes("row1"));

        delete.setTimestamp(1);

        delete.deleteColumn(Bytes.toBytes("colfam1"), Bytes.toBytes("qual1"));
        delete.deleteColumn(Bytes.toBytes("colfam1"), Bytes.toBytes("qual3"), 5);

        delete.deleteColumns(Bytes.toBytes("colfam1"), Bytes.toBytes("qual1"));
        delete.deleteColumns(Bytes.toBytes("colfam1"), Bytes.toBytes("qual3"), 6);

        delete.deleteFamily(Bytes.toBytes("colfam1"));
        delete.deleteFamily(Bytes.toBytes("colfam1"), 3);
        
        table.delete(delete);

        table.close();

        System.out.println("After delete call...");
        helper.dump("testtable", new String[] { "row1" }, null, null);
    }
}