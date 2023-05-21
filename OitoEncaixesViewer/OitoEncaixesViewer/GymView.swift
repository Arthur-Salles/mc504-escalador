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
        VStack {
            OutsideView()
                .background(Color.green)
                .environmentObject(gymViewModel)
            DoorView(gymCapacity: gymViewModel.gymCapacity)
            LineView(waitingUsers: $gymViewModel.waitingList)
            MachinesView(machines: $gymViewModel.machineModels)
            Spacer()
            HStack {
                Text("CAPACIDADE MÁXIMA: " + String(gymViewModel.gymCapacity))
                    .fontWeight(.bold)
                    .foregroundColor(.black)
                Spacer()
                Button(action: {
                    
                    gymViewModel.executeLogInstructions()
                }, label: {
                    Text("NEXT")
                        .fontWeight(.bold)
                        .foregroundColor(.black)
                })
            }
            .padding(20)
            
        }
        .background(.gray)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        GymView()
    }
}
