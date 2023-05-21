//
//  LineView.swift
//  SeisEncaixesViewer
//
//  Created by Ariadne Bigheti on 20/05/23.
//

import SwiftUI

struct LineView: View {
    @Binding var waitingUsers: [UserViewModel]
    private let adaptativeColumns = [
        GridItem(.adaptive(minimum: 100), alignment: .leading)
    ]
    
    var body: some View {
        if waitingUsers.isEmpty {
            VStack {
                Text("0/4")
                HStack {
                    Text("0")
                    Rectangle()
                        .frame(height: 50)
                }
            }
            .foregroundColor(.clear)
            .padding(20)
        } else {
            LazyVGrid(columns: adaptativeColumns, spacing: 30)  {
                ForEach($waitingUsers) { user in
                    UserView(viewModel: user)
                }
            }
            .padding(20)
        }
    }
}

