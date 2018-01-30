package util;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.client.HBaseAdmin;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.util.Bytes;

@SuppressWarnings("deprecation")
public class HBaseHelper {

    private Configuration conf = null;
    private HBaseAdmin admin = null;

    protected HBaseHelper(Configuration conf) throws IOException {
        this.conf = conf;
        this.admin = new HBaseAdmin(conf);
    }

    public static HBaseHelper getHelper(Configuration conf) throws IOException {
        return new HBaseHelper(conf);
    }

    public boolean existsTable(String table) throws IOException {
        return admin.tableExists(table);
    }

    public void createTable(String table, String... colfams) throws IOException {
        createTable(table, null, colfams);
    }

    public void createTable(String table, byte[][] splitKeys, String... colfams)
    throws IOException {
        HTableDescriptor desc = new HTableDescriptor(table);
        for (String cf : colfams) {
            HColumnDescriptor coldef = new HColumnDescriptor(cf);
            desc.addFamily(coldef);
        }
        if (splitKeys != null) {
            admin.createTable(desc, splitKeys);
        } else {
            admin.createTable(desc);
        }
    }

    public void disableTable(String table) throws IOException {
        admin.disableTable(table);
    }

    public void dropTable(String table) throws IOException {
        if (existsTable(table)) {
            disableTable(table);
            admin.deleteTable(table);
        }
    }

    public void put(String table, String[] rows, String[] fams, String[] quals,
                    long[] ts, String[] vals) throws IOException {
        HTable tbl = new HTable(conf, table);
        for (String row : rows) {
            Put put = new Put(Bytes.toBytes(row));
            for (String fam : fams) {
                int v = 0;
                for (String qual : quals) {
                    String val = vals[v < vals.length ? v : vals.length - 1];
                    long t = ts[v < ts.length ? v : ts.length - 1];
                    put.add(Bytes.toBytes(fam), Bytes.toBytes(qual), t,
                        Bytes.toBytes(val));
                    v++;
                }
            }
            tbl.put(put);
        }
        tbl.close();
    }
}
