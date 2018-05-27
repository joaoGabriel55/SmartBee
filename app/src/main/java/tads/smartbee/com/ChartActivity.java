package tads.smartbee.com;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

import tads.smartbee.com.FirebaseManager.FirebaseHandlerData;

public class ChartActivity extends AppCompatActivity {

    private FirebaseDatabase mFirebaseDatabase;
    private ChildEventListener childEventListener;
    private DatabaseReference temperaturaDate;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chart);

        temperaturaDate = FirebaseHandlerData.getmFirebaseDatabase().getReference().child("temperatureDate");

        GraphView graph = (GraphView) findViewById(R.id.graph);
        getTemperatureToChart(childEventListener, temperaturaDate, graph);

    }

    private DataPoint[] generateData(ArrayList<String> temps) throws ParseException {
        int count = 0;

        DataPoint[] values = new DataPoint[temps.size()];
        for (String temp : temps) {

            String[] vectorNode = temp.split(";");

            String date = vectorNode[0];

            Calendar calendar = Calendar.getInstance();

            SimpleDateFormat formato = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
            Date dateTemp = formato.parse(date);

            Double temperature =  Double.parseDouble(vectorNode[1]);

            if (temp != null) {
                DataPoint v = new DataPoint(count, temperature);
                values[count] = v;
                count++;
            }
        }
        return values;
    }

    public ArrayList<String> getTemperatureToChart(ChildEventListener childEventListener,
                                                   DatabaseReference databaseReference, final GraphView graphView) {
        final ArrayList<String> temps = new ArrayList<>();

            childEventListener = new ChildEventListener() {
                @Override
                public void onChildAdded(DataSnapshot dataSnapshot, String s) {
                    String temp = dataSnapshot.getValue(String.class);
                    temps.add(temp);

                    LineGraphSeries<DataPoint> series = null;
                    try {
                        series = new LineGraphSeries<>(generateData(temps));
                    } catch (ParseException e) {
                        e.printStackTrace();
                    }
                    graphView.addSeries(series);
                    graphView.setTitle("Temperatura ao longo do tempo");
                    Log.i("TESTEAGAIN", temp + "");
                }

                @Override
                public void onChildChanged(DataSnapshot dataSnapshot, String s) {

                }

                @Override
                public void onChildRemoved(DataSnapshot dataSnapshot) {

                }

                @Override
                public void onChildMoved(DataSnapshot dataSnapshot, String s) {

                }

                @Override
                public void onCancelled(DatabaseError databaseError) {

                }
            };
            databaseReference.addChildEventListener(childEventListener);

        return temps;
    }
}


