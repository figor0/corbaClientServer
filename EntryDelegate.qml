import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: entry
    Rectangle{
        id: first_name
        border.width: 1
        border.color: "black"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id: first_name_input
            anchors.fill: parent
            text: model.first_name
            readOnly: true
        }
    }
    Rectangle{
        id: last_name
        border.width: 1
        border.color: "black"
        anchors.left: first_name.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id: last_name_input
            anchors.fill: parent
            text: model.last_name
            readOnly: true
        }
    }
    Rectangle{
        id: father_name
        border.width: 1
        border.color: "black"
        anchors.left: last_name.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id :father_name_input
            anchors.fill: parent
            text: model.father_name
            readOnly: true
        }
    }
    Rectangle{
        id: phone
        border.width: 1
        border.color: "black"
        anchors.left: father_name.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width*0.20
        TextInput{
            id: phone_input
            anchors.fill: parent
            text: model.phone
            readOnly: true
        }
    }
}

