import QtQuick 2.0
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

Item {
    id: root
    property int action_type: 0
    function refresh(){
        menu.title = "Ничего не делать";
        action_type = 0;
    }
    Item{
        anchors.fill: parent
        Rectangle{
            color: "yellow"
            anchors.fill: parent
        }
        Text{
            id: menu_text
            anchors.fill: parent
            text: qsTr("Ничего не делать")
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                menu.open()
            }
        }
    }
    Menu{
        id: menu
        MenuItem{
            text: qsTr("Инвертировать записи")
            onTriggered: {
                action_type = 1;
                menu_text.text = text;
            }
        }
        MenuItem{
            text: qsTr("К маленькой букве")
            onTriggered: {
               menu_text.text = text;
               action_type = 2;
            }
        }
        MenuItem{
            text: qsTr("К большой букве")
            onTriggered: {
               menu_text.text = text;
               action_type = 3;
            }
        }
    }
}
