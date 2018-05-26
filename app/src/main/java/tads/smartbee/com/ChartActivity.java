package tads.smartbee.com;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

import java.util.ArrayList;
import java.util.Date;

import tads.smartbee.com.FirebaseManager.FirebaseHandlerData;

public class ChartActivity extends AppCompatActivity {

    private FirebaseDatabase mFirebaseDatabase;
    private ChildEventListener childEventListener;
    private DatabaseReference temperatura;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chart);

        temperatura = FirebaseHandlerData.getmFirebaseDatabase().getReference().child("temperature");
        ArrayList<Double> temps = new ArrayList<>();


        temps = getTemperatureToChart(childEventListener, temperatura);


        GraphView graph = (GraphView) findViewById(R.id.graph);
        LineGraphSeries<DataPoint> series = new LineGraphSeries<>(generateData(temps));
        graph.addSeries(series);
    }

    private DataPoint[] generateData(ArrayList<Double> temps) {
        int count = 0;
        DataPoint[] values = new DataPoint[temps.size()];
        for (Double temp : temps) {
            if (temp != null) {
                DataPoint v = new DataPoint(count, temp);
                values[count] = v;
                count++;
            }
        }
        return values;
    }

    public ArrayList<Double> getTemperatureToChart(ChildEventListener childEventListener, DatabaseReference databaseReference) {
        final ArrayList<Double> temps = new ArrayList<>();

        {

            childEventListener = new ChildEventListener() {
                @Override
                public void onChildAdded(DataSnapshot dataSnapshot, String s) {
                    Double temp = dataSnapshot.getValue(Double.class);
                    temps.add(temp);
                    generateData(temps);
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
        }
        return temps;
    }
}


