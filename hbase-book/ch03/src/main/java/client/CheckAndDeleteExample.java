package client;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.Delete;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.util.Bytes;
import util.HBaseHelper;

public class CheckAndDeleteExample {

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

        Delete delete1 = new Delete(Bytes.toBytes("row1"));
        delete1.deleteColumns(Bytes.toBytes("colfam1"), Bytes.toBytes("qual3"));

        boolean res1 = table.checkAndDelete(Bytes.toBytes("row1"),
            Bytes.toBytes("colfam2"), Bytes.toBytes("qual3"), null, delete1);
        System.out.println("Delete successful: " + res1);

        Delete delete2 = new Delete(Bytes.toBytes("row1"));
        delete2.deleteColumns(Bytes.toBytes("colfam2"), Bytes.toBytes("qual3"));
        table.delete(delete2);

        boolean res2 = table.checkAndDelete(Bytes.toBytes("row1"),
            Bytes.toBytes("colfam2"), Bytes.toBytes("qual3"), null, delete1);
        System.out.println("Delete successful: " + res2);

        Delete delete3 = new Delete(Bytes.toBytes("row2"));
        delete3.deleteFamily(Bytes.toBytes("colfam1"));

        try {
            boolean res4 = table.checkAndDelete(Bytes.toBytes("row1"),
                Bytes.toBytes("colfam1"), Bytes.toBytes("qual1"),
                Bytes.toBytes("val1"), delete3);
            System.out.println("Delete successful: " + res4);
        } catch (Exception e) {
            System.err.println("Error: " + e);
        }

        System.out.println("After delete call...");
        helper.dump("testtable", new String[] { "row1" }, null, null);
    }
}
