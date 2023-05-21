//
//  ContentView.swift
//  SeisEncaixesViewer
//
//  Created by Ariadne Bigheti on 18/05/23.
//

import SwiftUI

struct GymView: View {
    private let machineAdaptativeColumns = [
        GridItem(.adaptive(minimum: 210), alignment: .leading)
    ]
    @StateObject var gymViewModel: GymViewModel = GymViewModel()
    
    var body: some View {
        ScrollView {
            VStack(alignment: .center, spacing: 0) {
                OutsideView()
                    .environmentObject(gymViewModel)
                DoorView(gymCapacity: gymViewModel.gymCapacity)
                Image("oitoEncaixesLogo")
                    .resizable()
                    .frame(width: 270, height: 100)
                Text("CAPACIDADE MÁXIMA: " + String(gymViewModel.gymCapacity))
                    .font(.callout)
                    .fontWeight(.bold)
                    .foregroundColor(.black)
                LineView(waitingUsers: $gymViewModel.waitingList)
                MachinesView(machines: $gymViewModel.machineModels)
               HStack {
                    Spacer()
                    Button(action: {
                        
                        gymViewModel.executeLogInstructions()
                    }, label: {
                        Text("NEXT")
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                    })
                }.padding(30)
                
            }
        }
        .background(Color.gray.opacity(0.3))
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        GymView()
    }
}
