//
//  MachineView.swift
//  SeisEncaixesViewer
//
//  Created by Ariadne Bigheti on 18/05/23.
//

import SwiftUI

struct MachineView: View {
   @Binding var viewModel: MachineViewModel
    
    var body: some View {
        HStack {

            Image(viewModel.imageName)
                .resizable()
                .frame(width: 160, height: 160)
            
            if viewModel.isBeignUsed {
                if let user = viewModel.userUsing {
                    VStack {
                        Text("\(String(user.exercisesFinished)) / \(String(user.totalExercisesToDo))")
                        HStack {
                            Text(user.id)
                                .font(.title2)
                            Image(user.imageName)
                                .resizable()
                                .frame(width: 50, height: 50)
                        }
                    }

                }
            } else {
                HStack {
                    Text("0")
                        .font(.title2)
                        .foregroundColor(.clear)
                    Rectangle()
                        .foregroundColor(.clear)
                        .frame(width: 50, height: 50)
                }
                
            }
            
        }
        
    }
}
