//
//  UserView.swift
//  SeisEncaixesViewer
//
//  Created by Ariadne Bigheti on 18/05/23.
//

import SwiftUI

struct UserView: View {
    @Binding var viewModel: UserViewModel
    
    var body: some View {
        VStack {
            Text("\(String(viewModel.exercisesFinished)) / \(String(viewModel.totalExercisesToDo))")
            HStack {
                Text(viewModel.id)
                    .font(.title2)
                Image(viewModel.imageName)
                    .resizable()
                    .frame(width: 50, height: 50)
            }
        }
    }
}
