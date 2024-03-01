import SwiftUI

// TODO: Make the spacers actually work with the textfield or make the textfield less wide


struct MainView: View {
    @State private var command: String = ""

    var body: some View {
        VStack {
            Spacer()
            Text("This is Datistics")
            Spacer()
            HStack{
                TextField(
                    "enter commands here", 
                    text: $command
                )
                .disabled(false)
            }
            Spacer()
        }
        .padding()
    }
}
