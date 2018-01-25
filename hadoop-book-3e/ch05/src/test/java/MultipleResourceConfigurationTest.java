import static org.hamcrest.CoreMatchers.is;
import static org.junit.Assert.assertThat;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.junit.Test;

public class MultipleResourceConfigurationTest {

    @Test
    public void get() throws IOException {
        Configuration conf = new Configuration();
        conf.addResource("configuration-1.xml");
        conf.addResource("configuration-2.xml");

        assertThat(conf.get("color"), is("yellow"));
        assertThat(conf.getInt("size", 0), is(12));
        assertThat(conf.get("weight"), is("heavy"));
        assertThat(conf.get("size-weight"), is("12,heavy"));

        System.setProperty("size", "14");
        assertThat(conf.get("size-weight"), is("14,heavy"));

        System.setProperty("length", "2");
        assertThat(conf.get("length"), is((String) null));
    }
}
