import streamlit as st
import pandas as pd
import joblib
import requests
def get_thing_speak_data():
    url = 'Replace with the actual ReadAPIkey from ThingSpeak'

    response = requests.get(url)
    data = response.json()
    last_entry = data['feeds'][-1]
    return last_entry['field1']



def get_detection_status():
    try:
        with open("detection_status.txt", "r") as file:
            status = file.read()
        return status.strip()
    except FileNotFoundError:
        return "No information"


# Streamlit web app
st.title('Smart Parking Project')

model = joblib.load('parking_lot_model.pkl')


detection_status = get_detection_status()

if detection_status == '1':
    st.write('One Spot Occupied')
else:
    st.write('No Car Detected')

thing_speak_status = get_thing_speak_data()

st.write(f'Current Occupancy Status: {"Occupied" if thing_speak_status == "177622" and detection_status == "Car Detected" else "Available"}')



day_of_week = st.selectbox('Select Day of the Week', ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday'])

time_of_day = st.slider('Select Time of Day (hour)', min_value=0, max_value=23, value=12)

day_mapping = {'Monday': 0, 'Tuesday': 1, 'Wednesday': 2, 'Thursday': 3, 'Friday': 4, 'Saturday': 5, 'Sunday': 6}
numeric_day = day_mapping[day_of_week]

prediction_input = pd.DataFrame({'hour_of_day': [time_of_day], 'day_of_week': [numeric_day]})
predicted_occupancy = model.predict(prediction_input)

st.write(f'Probablility of the Spot Being Occupied: {round(predicted_occupancy[0]*100, 3)} %')
